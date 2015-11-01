//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestAxisAngle

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cmath>
#include "minimath/geom3d_ops.hpp"
#include "minimath/point3d.hpp"
#include "minimath/rotation3d.hpp"
#include "TestRotation3DUtils.h"

using minimath::axisangle;
using minimath::rotation3d;
using minimath::rotation3dx;
using minimath::rotation3dy;
using minimath::rotation3dz;

BOOST_AUTO_TEST_SUITE(TestAxisAngle)


BOOST_AUTO_TEST_CASE(testInstantiation)
{
  axisangle<double> rot1, rot2;
}

BOOST_AUTO_TEST_CASE(testDefaultEquality)
{
  BOOST_CHECK(axisangle<double>() == axisangle<double>());
}

BOOST_AUTO_TEST_CASE(testCopyConstruction)
{
  axisangle<double> rot1;
  axisangle<double> rot2(rot1);
  BOOST_CHECK(rot1 == rot2);
}

BOOST_AUTO_TEST_CASE(testAssignment)
{
  axisangle<double> rot1, rot2;
  rot2 = rot1;
  BOOST_CHECK(rot1 == rot2);
}

BOOST_AUTO_TEST_CASE(testNullRotation)
{
  axisangle<double> rot;
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = rotation3d<double>(rot)*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rotation3d<double>(rot)*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint45X)
{
  axisangle<double> rot(p100, PI/4.); // 45 degree rotation about X
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = rotation3d<double>(rot)*p010;
  BOOST_CHECK(pTest == pointxyzd(0., cos45, cos45));

  pTest = rotation3d<double>(rot)*p001;
  BOOST_CHECK(pTest == pointxyzd(0., -cos45, cos45));
}

BOOST_AUTO_TEST_CASE(testRotatePoint90X)
{
  axisangle<double> rot(p100, PI/2.); // 90 degree rotation about X
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = rotation3d<double>(rot)*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));

  pTest = rotation3d<double>(rot)*p001;
  BOOST_CHECK(pTest == pointxyzd(0., -1., 0.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint180X)
{
  axisangle<double> rot(p100, PI); // 180 degree rotation about X

  pointxyzd pTest = rotation3d<double>(rot)*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = rotation3d<double>(rot)*p010;
  BOOST_CHECK(pTest == pointxyzd(0., -1., 0.));

  pTest = rotation3d<double>(rot)*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., -1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint45Y)
{
  axisangle<double> rot(p010, PI/4.); // 45 degree rotation about Y
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  BOOST_CHECK(pTest == pointxyzd(cos45, 0., -cos45));

  pTest = rotation3d<double>(rot)*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0));

  pTest = rotation3d<double>(rot)*p001;
  BOOST_CHECK(pTest == pointxyzd(cos45, 0, cos45));
}

BOOST_AUTO_TEST_CASE(testRotatePoint90Y)
{
  axisangle<double> rot(p010, PI/2.); // 90 degree rotation about Y
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  BOOST_CHECK(pTest == pointxyzd(0., 0., -1.));

  pTest = rotation3d<double>(rot)*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rotation3d<double>(rot)*p001;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint180Y)
{
  axisangle<double> rot(p010, PI); // 180 degree rotation about Y

  pointxyzd pTest = rotation3d<double>(rot)*p100;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = rotation3d<double>(rot)*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rotation3d<double>(rot)*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., -1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint45Z)
{
  axisangle<double> rot(p001, PI/4.); // 45 degree rotation about Z
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  BOOST_CHECK(pTest == pointxyzd(cos45, cos45, 0.));

  pTest = rotation3d<double>(rot)*p010;
  BOOST_CHECK(pTest == pointxyzd(-cos45, cos45, 0));

  pTest = rotation3d<double>(rot)*p001;
  BOOST_CHECK(pTest == pointxyzd(0, 0, 1));
}

BOOST_AUTO_TEST_CASE(testRotatePoint90Z)
{
  axisangle<double> rot(p001, PI/2.); // 90 degree rotation about Z
  pointxyzd pTest = rotation3d<double>(rot)*p100;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rotation3d<double>(rot)*p010;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = rotation3d<double>(rot)*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint180Z)
{
  axisangle<double> rot(p001, PI); // 180 degree rotation about Z

  pointxyzd pTest = rotation3d<double>(rot)*p100;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = rotation3d<double>(rot)*p010;
  BOOST_CHECK(pTest == pointxyzd(0., -1., 0.));

  pTest = rotation3d<double>(rot)*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testAssignRotation3DX)
{
  for (int i = 1; i < 9; ++i) {
    BOOST_CHECK(axisangle<double>(p100, PI/i) == rotation3dx<double>(PI/i));
  }
}

BOOST_AUTO_TEST_CASE(testAssignRotation3DY)
{
  for (int i = 1; i < 9; ++i) {
    BOOST_CHECK(axisangle<double>(p010, PI/i) == rotation3dy<double>(PI/i));
  }
}


BOOST_AUTO_TEST_CASE(testAssignRotation3DZ)
{
  for (int i = 1; i < 9; ++i) {
    BOOST_CHECK(axisangle<double>(p001, PI/i) == rotation3dz<double>(PI/i));
  }
}

BOOST_AUTO_TEST_CASE(testInverse)
{
  BOOST_CHECK(TestUtils::testInverseAxisAngle(p100));
  BOOST_CHECK(TestUtils::testInverseAxisAngle(p010));
  BOOST_CHECK(TestUtils::testInverseAxisAngle(p001));
}

BOOST_AUTO_TEST_CASE(testInvert)
{
  BOOST_CHECK(TestUtils::testInvertAxisAngle(p100));
  BOOST_CHECK(TestUtils::testInvertAxisAngle(p010));
  BOOST_CHECK(TestUtils::testInvertAxisAngle(p001));
}

BOOST_AUTO_TEST_SUITE_END()
