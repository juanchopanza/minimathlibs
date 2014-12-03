//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#include <iostream>
#include <cmath>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "minimath/matrix.hpp"
#include "minimath/matrix_ops.hpp"
#include "minimath/rotation3d.hpp"
#include "minimath/point3d.hpp"
#include "minimath/geom3d_ops.hpp"

#include "TestRotation3DUtils.h"
#include "TestRotation3D.h"
#include "Defines.h"


using namespace minimath;

void TestRotation3D::testInstantiation()
{
  rotation3d<double> rot1, rot2;
}
void TestRotation3D::testDefaultEquality()
{
  CPPUNIT_ASSERT(rotation3d<double>() == rotation3d<double>());
}
void TestRotation3D::testCopyConstruction()
{
  rotation3d<double> rot1;
  rotation3d<double> rot2(rot1);
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3D::testAssignment()
{
  rotation3d<double> rot1, rot2;
  rot2 = rot1;
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3D::testNullRotation()
{
  rotation3d<double> rot;
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., 1.));
}

void TestRotation3D::testRotatePoint45X()
{
  rotation3d<double> rot = rotation3dx<double>(PI/4.); // 45 degree rotation about X
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., cos45, cos45));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., -cos45, cos45));
}

void TestRotation3D::testRotatePoint90X()
{
  rotation3d<double> rot = rotation3dx<double>(PI/2.); // 90 degree rotation about X
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., 1.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., -1., 0.));
}

void TestRotation3D::testRotatePoint180X()
{
  rotation3d<double> rot = rotation3dx<double>(PI); // 180 degree rotation about X

  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., -1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., -1.));
}

void TestRotation3D::testRotatePoint45Y()
{
  rotation3d<double> rot = rotation3dy<double> (PI/4.); // 45 degree rotation about X
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(cos45, 0., -cos45));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(cos45, 0, cos45));
}

void TestRotation3D::testRotatePoint90Y()
{
  rotation3d<double> rot = rotation3dy<double> (PI/2.); // 90 degree rotation about X
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., -1.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));
}

void TestRotation3D::testRotatePoint180Y()
{
  rotation3d<double> rot = rotation3dy<double> (PI); // 180 degree rotation about X

  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(-1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., -1.));
}

void TestRotation3D::testRotatePoint45Z()
{
  rotation3d<double> rot = rotation3dz<double>(PI/4.); // 45 degree rotation about Z
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(cos45, cos45, 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(-cos45, cos45, 0));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0, 0, 1));
}

void TestRotation3D::testRotatePoint90Z()
{
  rotation3d<double> rot = rotation3dz<double>(PI/2.); // 90 degree rotation about Z
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(-1., 0., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., 1.));
}

void TestRotation3D::testRotatePoint180Z()
{
  rotation3d<double> rot = rotation3dz<double>(PI); // 180 degree rotation about Z

  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(-1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., -1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., 1.));
}

void TestRotation3D::testInverse()
{
  CPPUNIT_ASSERT(TestUtils::testInverseRotation3D<rotation3dx<double> >());
  CPPUNIT_ASSERT(TestUtils::testInverseRotation3D<rotation3dy<double> >());
  CPPUNIT_ASSERT(TestUtils::testInverseRotation3D<rotation3dz<double> >());
}

void TestRotation3D::testInvert()
{
  CPPUNIT_ASSERT(TestUtils::testInvertRotation3D<rotation3dx<double> >());
  CPPUNIT_ASSERT(TestUtils::testInvertRotation3D<rotation3dy<double> >());
  CPPUNIT_ASSERT(TestUtils::testInvertRotation3D<rotation3dz<double> >());
}

void TestRotation3D::testFindTransformationRotX()
{
  TestUtils::testFindTransformationAxisRot<rotation3dx<double> >();
}

void TestRotation3D::testFindTransformationRotY()
{
  TestUtils::testFindTransformationAxisRot<rotation3dy<double> >();
}

void TestRotation3D::testFindTransformationRotZ()
{
  TestUtils::testFindTransformationAxisRot<rotation3dz<double> >();
}

