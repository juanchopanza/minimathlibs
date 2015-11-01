//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestRotation3DZYX
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cmath>
#include "minimath/rotation3d.hpp"
#include "minimath/point3d.hpp"
#include "Defines.h"
#include "TestRotation3DUtils.h"

using namespace minimath;

BOOST_AUTO_TEST_SUITE(TestRotation3DZYX)

namespace
{

//
// Check that a RotationZYX defined by angles phi, theta, psi has the same
// effect on a point as individual Z, Y and X rotations.
//
bool testRotationZYX(const minimath::pointxyzd& point,
                     double phi, 
                     double theta, 
                     double psi)
{ 
  rotation3dzyx<double> rot1(phi, theta, psi);
  pointxyzd ref = rotation3dx<double>(psi) *
      ( rotation3dy<double>(theta) * (rotation3dz<double>(phi)*point) );
  return rot1*point == ref;
}

} // namespace

BOOST_AUTO_TEST_CASE(testInstantiation)
{
  rotation3dzyx<double> rot1, rot2;
}

BOOST_AUTO_TEST_CASE(testDefaultEquality)
{
  BOOST_CHECK(rotation3dzyx<double>() == rotation3dzyx<double>());
}

BOOST_AUTO_TEST_CASE(testCopyConstruction)
{
  rotation3dzyx<double> rot1;
  rotation3dzyx<double> rot2(rot1);
  BOOST_CHECK(rot1 == rot2);
}

BOOST_AUTO_TEST_CASE(testAssignment)
{
  rotation3dzyx<double> rot1, rot2;
  rot2 = rot1;
  BOOST_CHECK(rot1 == rot2);
}

BOOST_AUTO_TEST_CASE(testNullRotation)
{
  rotation3dzyx<double> rot;
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint45X)
{
  rotation3dzyx<double> rot(0, 0, PI/4.); // 45 degree rotation about X
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., cos45, cos45));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., -cos45, cos45));
}

BOOST_AUTO_TEST_CASE(testRotatePoint90X)
{
  rotation3dzyx<double> rot(0, 0, PI/2.); // 90 degree rotation about X
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., -1., 0.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint180X)
{
  rotation3dzyx<double> rot(0, 0, PI); // 180 degree rotation about X

  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., -1., 0.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., -1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint45Y)
{
  rotation3dzyx<double> rot(0, PI/4., 0); // 45 degree rotation about X
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(cos45, 0., -cos45));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(cos45, 0, cos45));
}

BOOST_AUTO_TEST_CASE(testRotatePoint90Y)
{
  rotation3dzyx<double> rot(0, PI/2., 0); // 90 degree rotation about X
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(0., 0., -1.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint180Y)
{
  rotation3dzyx<double> rot(0, PI, 0); // 180 degree rotation about X

  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., -1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint45Z)
{
  rotation3dzyx<double> rot(PI/4., 0, 0); // 45 degree rotation about Z
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(cos45, cos45, 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(-cos45, cos45, 0));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0, 0, 1));
}

BOOST_AUTO_TEST_CASE(testRotatePoint90Z)
{
  rotation3dzyx<double> rot(PI/2., 0, 0); // 90 degree rotation about Z
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint180Z)
{
  rotation3dzyx<double> rot(PI, 0, 0); // 180 degree rotation about Z

  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., -1., 0.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testAssignRotation3DX)
{
  for (int i = 1; i < 9; ++i) {
    BOOST_CHECK(rotation3dzyx<double>(0, 0, PI/i) == rotation3dx<double>(PI/i));
  }
}

BOOST_AUTO_TEST_CASE(testAssignRotation3DY)
{
  for (int i = 1; i < 9; ++i) {
    BOOST_CHECK(rotation3dzyx<double>(0, PI/i, 0) == rotation3dy<double>(PI/i));
  }
}


BOOST_AUTO_TEST_CASE(testAssignRotation3DZ)
{
  for (int i = 1; i < 9; ++i) {
    BOOST_CHECK(rotation3dzyx<double>(PI/i, 0, 0) == rotation3dz<double>(PI/i));
  }
}

BOOST_AUTO_TEST_CASE(testZYXRotations)
{
  for (int i = 1; i < 9; ++i) {

    const double angle = PI/i;

    BOOST_CHECK(testRotationZYX(p100, angle, angle, angle));
    BOOST_CHECK(testRotationZYX(p010, angle, angle, angle));
    BOOST_CHECK(testRotationZYX(p001, angle, angle, angle)); 

    BOOST_CHECK(testRotationZYX(p100, -angle, angle, angle));
    BOOST_CHECK(testRotationZYX(p010, angle, angle, angle));
    BOOST_CHECK(testRotationZYX(p001, angle, angle, angle)); 

    BOOST_CHECK(testRotationZYX(p100, angle, angle, angle));
    BOOST_CHECK(testRotationZYX(p010, -angle, angle, angle));
    BOOST_CHECK(testRotationZYX(p001, angle, angle, angle)); 

    BOOST_CHECK(testRotationZYX(p100, angle, -angle, angle));
    BOOST_CHECK(testRotationZYX(p010, angle, -angle, angle));
    BOOST_CHECK(testRotationZYX(p001, angle, -angle, angle)); 

    BOOST_CHECK(testRotationZYX(p100, -angle, -angle, -angle));
    BOOST_CHECK(testRotationZYX(p010, -angle, -angle, -angle));
    BOOST_CHECK(testRotationZYX(p001, -angle, -angle, -angle)); 

  }
}

BOOST_AUTO_TEST_CASE(testInverse)
{
  BOOST_CHECK(TestUtils::testInverseRotation3DZYX<rotation3dx<double> >());
  BOOST_CHECK(TestUtils::testInverseRotation3DZYX<rotation3dy<double> >());
  BOOST_CHECK(TestUtils::testInverseRotation3DZYX<rotation3dz<double> >());
}

BOOST_AUTO_TEST_CASE(testInvert)
{
  BOOST_CHECK(TestUtils::testInvertRotation3DZYX<rotation3dx<double> >());
  BOOST_CHECK(TestUtils::testInvertRotation3DZYX<rotation3dy<double> >());
  BOOST_CHECK(TestUtils::testInvertRotation3DZYX<rotation3dz<double> >());
}

BOOST_AUTO_TEST_SUITE_END()
