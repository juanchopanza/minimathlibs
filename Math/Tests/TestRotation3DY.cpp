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

#include "Math/Rotation3D.h"
#include "Math/Point3D.h"

#include "Defines.h"
#include "TestRotation3DUtils.h"
#include "TestRotation3DY.h"

using namespace Math;

void TestRotation3DY::testInstantiation()
{
  Rotation3DY<double> rot1, rot2;
}
void TestRotation3DY::testDefaultEquality()
{
  CPPUNIT_ASSERT(Rotation3DY<double>() == Rotation3DY<double>());
}
void TestRotation3DY::testCopyConstruction()
{
  Rotation3DY<double> rot1;
  Rotation3DY<double> rot2(rot1);
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3DY::testAssignment()
{
  Rotation3DY<double> rot1, rot2;
  rot2 = rot1;
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3DY::testRotatePoint0()
{
  Rotation3DY<double> rotx4(0);
  PointXYZD pTest = rotx4*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = rotx4*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = rotx4*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestRotation3DY::testRotatePoint45()
{
  Rotation3DY<double> rotx6(PI/4.); // 45 degree rotation about X
  PointXYZD pTest = rotx6*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0., -cos45));

  pTest = rotx6*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0));

  pTest = rotx6*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0, cos45));
}

void TestRotation3DY::testRotatePoint90()
{
  Rotation3DY<double> rotx4(PI/2.); // 90 degree rotation about X
  PointXYZD pTest = rotx4*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));

  pTest = rotx4*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = rotx4*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));
}

void TestRotation3DY::testRotatePoint180()
{
  Rotation3DY<double> rotx5(PI); // 180 degree rotation about X

  PointXYZD pTest = rotx5*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = rotx5*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = rotx5*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
}

void TestRotation3DY::testInverse()
{
  CPPUNIT_ASSERT(TestUtils::testInverse<Rotation3DY<double> >());
}

void TestRotation3DY::testInvert()
{
  CPPUNIT_ASSERT(TestUtils::testInvert<Rotation3DY<double> >());
}
