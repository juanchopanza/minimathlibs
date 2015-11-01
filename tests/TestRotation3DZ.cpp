//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestRotation3DZ
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cmath>
#include "minimath/rotation3d.hpp"
#include "minimath/point3d.hpp"
#include "Defines.h"
#include "TestRotation3DUtils.h"

using namespace minimath;

BOOST_AUTO_TEST_SUITE(TestRotation3DZ)

BOOST_AUTO_TEST_CASE(testInstantiation)
{
  rotation3dz<double> rot1, rot2;
}

BOOST_AUTO_TEST_CASE(testDefaultEquality)
{
  BOOST_CHECK(rotation3dz<double>() == rotation3dz<double>());
}

BOOST_AUTO_TEST_CASE(testCopyConstruction)
{
  rotation3dz<double> rot1;
  rotation3dz<double> rot2(rot1);
  BOOST_CHECK(rot1 == rot2);
}

BOOST_AUTO_TEST_CASE(testAssignment)
{
  rotation3dz<double> rot1, rot2;
  rot2 = rot1;
  BOOST_CHECK(rot1 == rot2);
}

BOOST_AUTO_TEST_CASE(testRotatePoint0)
{
  rotation3dz<double> rotx4(0);
  pointxyzd pTest = rotx4*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = rotx4*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rotx4*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint45)
{
  rotation3dz<double> rotx6(PI/4.); // 45 degree rotation about Z
  pointxyzd pTest = rotx6*p100;
  BOOST_CHECK(pTest == pointxyzd(cos45, cos45, 0.));

  pTest = rotx6*p010;
  BOOST_CHECK(pTest == pointxyzd(-cos45, cos45, 0));

  pTest = rotx6*p001;
  BOOST_CHECK(pTest == pointxyzd(0, 0, 1));
}

BOOST_AUTO_TEST_CASE(testRotatePoint90)
{
  rotation3dz<double> rotx4(PI/2.); // 90 degree rotation about Z
  pointxyzd pTest = rotx4*p100;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rotx4*p010;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = rotx4*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint180)
{
  rotation3dz<double> rotx5(PI); // 180 degree rotation about Z

  pointxyzd pTest = rotx5*p100;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = rotx5*p010;
  BOOST_CHECK(pTest == pointxyzd(0., -1., 0.));

  pTest = rotx5*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testInverse)
{
  BOOST_CHECK(TestUtils::testInverse<rotation3dz<double> >());
}

BOOST_AUTO_TEST_CASE(testInvert)
{
  BOOST_CHECK(TestUtils::testInvert<rotation3dz<double> >());
}

BOOST_AUTO_TEST_SUITE_END()
