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

#include "Math/Geom3DOps.h"
#include "Math/Point3D.h"
#include "Math/Rotation3D.h"

#include "TestAxisAngle.h"

#include "TestRotation3DUtils.h"
//using namespace Math;

using Math::AxisAngle;
using Math::Rotation3D;
using Math::Rotation3DX;
using Math::Rotation3DY;
using Math::Rotation3DZ;

void TestAxisAngle::testInstantiation()
{
  AxisAngle<double> rot1, rot2;
}

void TestAxisAngle::testDefaultEquality()
{
  CPPUNIT_ASSERT(AxisAngle<double>() == AxisAngle<double>());
}

void TestAxisAngle::testCopyConstruction()
{
  AxisAngle<double> rot1;
  AxisAngle<double> rot2(rot1);
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestAxisAngle::testAssignment()
{
  AxisAngle<double> rot1, rot2;
  rot2 = rot1;
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestAxisAngle::testNullRotation()
{
  AxisAngle<double> rot;
  PointXYZD pTest = Rotation3D<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = Rotation3D<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = Rotation3D<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestAxisAngle::testRotatePoint45X()
{
  AxisAngle<double> rot(p100, PI/4.); // 45 degree rotation about X
  PointXYZD pTest = Rotation3D<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = Rotation3D<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., cos45, cos45));

  pTest = Rotation3D<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -cos45, cos45));
}

void TestAxisAngle::testRotatePoint90X()
{
  AxisAngle<double> rot(p100, PI/2.); // 90 degree rotation about X
  PointXYZD pTest = Rotation3D<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = Rotation3D<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));

  pTest = Rotation3D<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));
}

void TestAxisAngle::testRotatePoint180X()
{
  AxisAngle<double> rot(p100, PI); // 180 degree rotation about X

  PointXYZD pTest = Rotation3D<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = Rotation3D<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

  pTest = Rotation3D<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
}

void TestAxisAngle::testRotatePoint45Y()
{
  AxisAngle<double> rot(p010, PI/4.); // 45 degree rotation about Y
  PointXYZD pTest = Rotation3D<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0., -cos45));

  pTest = Rotation3D<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0));

  pTest = Rotation3D<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0, cos45));
}

void TestAxisAngle::testRotatePoint90Y()
{
  AxisAngle<double> rot(p010, PI/2.); // 90 degree rotation about Y
  PointXYZD pTest = Rotation3D<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));

  pTest = Rotation3D<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = Rotation3D<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));
}

void TestAxisAngle::testRotatePoint180Y()
{
  AxisAngle<double> rot(p010, PI); // 180 degree rotation about Y

  PointXYZD pTest = Rotation3D<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = Rotation3D<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = Rotation3D<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
}

void TestAxisAngle::testRotatePoint45Z()
{
  AxisAngle<double> rot(p001, PI/4.); // 45 degree rotation about Z
  PointXYZD pTest = Rotation3D<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, cos45, 0.));

  pTest = Rotation3D<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(-cos45, cos45, 0));

  pTest = Rotation3D<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0, 0, 1));
}

void TestAxisAngle::testRotatePoint90Z()
{
  AxisAngle<double> rot(p001, PI/2.); // 90 degree rotation about Z
  PointXYZD pTest = Rotation3D<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = Rotation3D<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = Rotation3D<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestAxisAngle::testRotatePoint180Z()
{
  AxisAngle<double> rot(p001, PI); // 180 degree rotation about Z

  PointXYZD pTest = Rotation3D<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = Rotation3D<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

  pTest = Rotation3D<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestAxisAngle::testAssignRotation3DX()
{
  for (int i = 1; i < 9; ++i) {
    CPPUNIT_ASSERT(AxisAngle<double>(p100, PI/i) == Rotation3DX<double>(PI/i));
  }
}

void TestAxisAngle::testAssignRotation3DY()
{
  for (int i = 1; i < 9; ++i) {
    CPPUNIT_ASSERT(AxisAngle<double>(p010, PI/i) == Rotation3DY<double>(PI/i));
  }
}


void TestAxisAngle::testAssignRotation3DZ()
{
  for (int i = 1; i < 9; ++i) {
    CPPUNIT_ASSERT(AxisAngle<double>(p001, PI/i) == Rotation3DZ<double>(PI/i));
  }
}

void TestAxisAngle::testInverse()
{
  CPPUNIT_ASSERT(TestUtils::testInverseAxisAngle(p100));
  CPPUNIT_ASSERT(TestUtils::testInverseAxisAngle(p010));
  CPPUNIT_ASSERT(TestUtils::testInverseAxisAngle(p001));
}

void TestAxisAngle::testInvert()
{
  CPPUNIT_ASSERT(TestUtils::testInvertAxisAngle(p100));
  CPPUNIT_ASSERT(TestUtils::testInvertAxisAngle(p010));
  CPPUNIT_ASSERT(TestUtils::testInvertAxisAngle(p001));
}
