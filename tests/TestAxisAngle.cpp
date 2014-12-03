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

#include "minimath/geom3d_ops.hpp"
#include "minimath/point3d.hpp"
#include "minimath/rotation3d.hpp"

#include "TestAxisAngle.h"

#include "TestRotation3DUtils.h"
//using namespace minimath;

using minimath::axisangle;
using minimath::rotation3d;
using minimath::rotation3dx;
using minimath::rotation3dy;
using minimath::rotation3dz;

void TestAxisAngle::testInstantiation()
{
  axisangle<double> rot1, rot2;
}

void TestAxisAngle::testDefaultEquality()
{
  CPPUNIT_ASSERT(axisangle<double>() == axisangle<double>());
}

void TestAxisAngle::testCopyConstruction()
{
  axisangle<double> rot1;
  axisangle<double> rot2(rot1);
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestAxisAngle::testAssignment()
{
  axisangle<double> rot1, rot2;
  rot2 = rot1;
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestAxisAngle::testNullRotation()
{
  axisangle<double> rot;
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));

  pTest = rotation3d<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rotation3d<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., 1.));
}

void TestAxisAngle::testRotatePoint45X()
{
  axisangle<double> rot(p100, PI/4.); // 45 degree rotation about X
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));

  pTest = rotation3d<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., cos45, cos45));

  pTest = rotation3d<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., -cos45, cos45));
}

void TestAxisAngle::testRotatePoint90X()
{
  axisangle<double> rot(p100, PI/2.); // 90 degree rotation about X
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));

  pTest = rotation3d<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., 1.));

  pTest = rotation3d<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., -1., 0.));
}

void TestAxisAngle::testRotatePoint180X()
{
  axisangle<double> rot(p100, PI); // 180 degree rotation about X

  pointxyzd pTest = rotation3d<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));

  pTest = rotation3d<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., -1., 0.));

  pTest = rotation3d<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., -1.));
}

void TestAxisAngle::testRotatePoint45Y()
{
  axisangle<double> rot(p010, PI/4.); // 45 degree rotation about Y
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(cos45, 0., -cos45));

  pTest = rotation3d<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0));

  pTest = rotation3d<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(cos45, 0, cos45));
}

void TestAxisAngle::testRotatePoint90Y()
{
  axisangle<double> rot(p010, PI/2.); // 90 degree rotation about Y
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., -1.));

  pTest = rotation3d<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rotation3d<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));
}

void TestAxisAngle::testRotatePoint180Y()
{
  axisangle<double> rot(p010, PI); // 180 degree rotation about Y

  pointxyzd pTest = rotation3d<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(-1., 0., 0.));

  pTest = rotation3d<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rotation3d<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., -1.));
}

void TestAxisAngle::testRotatePoint45Z()
{
  axisangle<double> rot(p001, PI/4.); // 45 degree rotation about Z
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(cos45, cos45, 0.));

  pTest = rotation3d<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(-cos45, cos45, 0));

  pTest = rotation3d<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0, 0, 1));
}

void TestAxisAngle::testRotatePoint90Z()
{
  axisangle<double> rot(p001, PI/2.); // 90 degree rotation about Z
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rotation3d<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(-1., 0., 0.));

  pTest = rotation3d<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., 1.));
}

void TestAxisAngle::testRotatePoint180Z()
{
  axisangle<double> rot(p001, PI); // 180 degree rotation about Z

  pointxyzd pTest = rotation3d<double>(rot)*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(-1., 0., 0.));

  pTest = rotation3d<double>(rot)*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., -1., 0.));

  pTest = rotation3d<double>(rot)*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., 1.));
}

void TestAxisAngle::testAssignRotation3DX()
{
  for (int i = 1; i < 9; ++i) {
    CPPUNIT_ASSERT(axisangle<double>(p100, PI/i) == rotation3dx<double>(PI/i));
  }
}

void TestAxisAngle::testAssignRotation3DY()
{
  for (int i = 1; i < 9; ++i) {
    CPPUNIT_ASSERT(axisangle<double>(p010, PI/i) == rotation3dy<double>(PI/i));
  }
}


void TestAxisAngle::testAssignRotation3DZ()
{
  for (int i = 1; i < 9; ++i) {
    CPPUNIT_ASSERT(axisangle<double>(p001, PI/i) == rotation3dz<double>(PI/i));
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
