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

#include "Math/Matrix.h"
#include "Math/MatrixOps.h"
#include "Math/Rotation3D.h"
#include "Math/Point3D.h"
#include "Math/Geom3DOps.h"

#include "TestRotation3DUtils.h"
#include "TestRotation3D.h"
#include "Defines.h"


using namespace Math;

void TestRotation3D::testInstantiation()
{
  Rotation3D<double> rot1, rot2;
}
void TestRotation3D::testDefaultEquality()
{
  CPPUNIT_ASSERT(Rotation3D<double>() == Rotation3D<double>());
}
void TestRotation3D::testCopyConstruction()
{
  Rotation3D<double> rot1;
  Rotation3D<double> rot2(rot1);
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3D::testAssignment()
{
  Rotation3D<double> rot1, rot2;
  rot2 = rot1;
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3D::testNullRotation()
{
  Rotation3D<double> rot;
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestRotation3D::testRotatePoint45X()
{
  Rotation3D<double> rot = Rotation3DX<double>(PI/4.); // 45 degree rotation about X
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., cos45, cos45));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -cos45, cos45));
}

void TestRotation3D::testRotatePoint90X()
{
  Rotation3D<double> rot = Rotation3DX<double>(PI/2.); // 90 degree rotation about X
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));
}

void TestRotation3D::testRotatePoint180X()
{
  Rotation3D<double> rot = Rotation3DX<double>(PI); // 180 degree rotation about X

  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
}

void TestRotation3D::testRotatePoint45Y()
{
  Rotation3D<double> rot = Rotation3DY<double> (PI/4.); // 45 degree rotation about X
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0., -cos45));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0, cos45));
}

void TestRotation3D::testRotatePoint90Y()
{
  Rotation3D<double> rot = Rotation3DY<double> (PI/2.); // 90 degree rotation about X
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));
}

void TestRotation3D::testRotatePoint180Y()
{
  Rotation3D<double> rot = Rotation3DY<double> (PI); // 180 degree rotation about X

  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
}

void TestRotation3D::testRotatePoint45Z()
{
  Rotation3D<double> rot = Rotation3DZ<double>(PI/4.); // 45 degree rotation about Z
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, cos45, 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(-cos45, cos45, 0));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0, 0, 1));
}

void TestRotation3D::testRotatePoint90Z()
{
  Rotation3D<double> rot = Rotation3DZ<double>(PI/2.); // 90 degree rotation about Z
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestRotation3D::testRotatePoint180Z()
{
  Rotation3D<double> rot = Rotation3DZ<double>(PI); // 180 degree rotation about Z

  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestRotation3D::testInverse()
{
  CPPUNIT_ASSERT(TestUtils::testInverseRotation3D<Rotation3DX<double> >());
  CPPUNIT_ASSERT(TestUtils::testInverseRotation3D<Rotation3DY<double> >());
  CPPUNIT_ASSERT(TestUtils::testInverseRotation3D<Rotation3DZ<double> >());
}

void TestRotation3D::testInvert()
{
  CPPUNIT_ASSERT(TestUtils::testInvertRotation3D<Rotation3DX<double> >());
  CPPUNIT_ASSERT(TestUtils::testInvertRotation3D<Rotation3DY<double> >());
  CPPUNIT_ASSERT(TestUtils::testInvertRotation3D<Rotation3DZ<double> >());
}

void TestRotation3D::testFindTransformationRotX()
{
  TestUtils::testFindTransformationAxisRot<Rotation3DX<double> >();
}

void TestRotation3D::testFindTransformationRotY()
{
  TestUtils::testFindTransformationAxisRot<Rotation3DY<double> >();
}

void TestRotation3D::testFindTransformationRotZ()
{
  TestUtils::testFindTransformationAxisRot<Rotation3DZ<double> >();
}

