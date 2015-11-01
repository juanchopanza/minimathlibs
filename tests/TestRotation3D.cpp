//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestRotation3D
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cmath>
#include "minimath/matrix.hpp"
#include "minimath/matrix_ops.hpp"
#include "minimath/rotation3d.hpp"
#include "minimath/point3d.hpp"
#include "minimath/geom3d_ops.hpp"
#include "TestRotation3DUtils.h"
#include "Defines.h"


using namespace minimath;

BOOST_AUTO_TEST_SUITE(TestRotation3D)


BOOST_AUTO_TEST_CASE(testInstantiation)
{
  rotation3d<double> rot1, rot2;
}

BOOST_AUTO_TEST_CASE(testDefaultEquality)
{
  BOOST_CHECK(rotation3d<double>() == rotation3d<double>());
}

BOOST_AUTO_TEST_CASE(testCopyConstruction)
{
  rotation3d<double> rot1;
  rotation3d<double> rot2(rot1);
  BOOST_CHECK(rot1 == rot2);
}

BOOST_AUTO_TEST_CASE(testAssignment)
{
  rotation3d<double> rot1, rot2;
  rot2 = rot1;
  BOOST_CHECK(rot1 == rot2);
}

BOOST_AUTO_TEST_CASE(testNullRotation)
{
  rotation3d<double> rot;
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint45X)
{
  rotation3d<double> rot = rotation3dx<double>(PI/4.); // 45 degree rotation about X
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., cos45, cos45));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., -cos45, cos45));
}

BOOST_AUTO_TEST_CASE(testRotatePoint90X)
{
  rotation3d<double> rot = rotation3dx<double>(PI/2.); // 90 degree rotation about X
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., -1., 0.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint180X)
{
  rotation3d<double> rot = rotation3dx<double>(PI); // 180 degree rotation about X

  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., -1., 0.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., -1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint45Y)
{
  rotation3d<double> rot = rotation3dy<double> (PI/4.); // 45 degree rotation about X
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(cos45, 0., -cos45));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(cos45, 0, cos45));
}

BOOST_AUTO_TEST_CASE(testRotatePoint90Y)
{
  rotation3d<double> rot = rotation3dy<double> (PI/2.); // 90 degree rotation about X
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(0., 0., -1.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint180Y)
{
  rotation3d<double> rot = rotation3dy<double> (PI); // 180 degree rotation about X

  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., -1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint45Z)
{
  rotation3d<double> rot = rotation3dz<double>(PI/4.); // 45 degree rotation about Z
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(cos45, cos45, 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(-cos45, cos45, 0));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0, 0, 1));
}

BOOST_AUTO_TEST_CASE(testRotatePoint90Z)
{
  rotation3d<double> rot = rotation3dz<double>(PI/2.); // 90 degree rotation about Z
  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testRotatePoint180Z)
{
  rotation3d<double> rot = rotation3dz<double>(PI); // 180 degree rotation about Z

  pointxyzd pTest = rot*p100;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = rot*p010;
  BOOST_CHECK(pTest == pointxyzd(0., -1., 0.));

  pTest = rot*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testInverse)
{
  BOOST_CHECK(TestUtils::testInverseRotation3D<rotation3dx<double> >());
  BOOST_CHECK(TestUtils::testInverseRotation3D<rotation3dy<double> >());
  BOOST_CHECK(TestUtils::testInverseRotation3D<rotation3dz<double> >());
}

BOOST_AUTO_TEST_CASE(testInvert)
{
  BOOST_CHECK(TestUtils::testInvertRotation3D<rotation3dx<double> >());
  BOOST_CHECK(TestUtils::testInvertRotation3D<rotation3dy<double> >());
  BOOST_CHECK(TestUtils::testInvertRotation3D<rotation3dz<double> >());
}

BOOST_AUTO_TEST_CASE(testFindTransformationRotX)
{
  TestUtils::testFindTransformationAxisRot<rotation3dx<double> >();
}

BOOST_AUTO_TEST_CASE(testFindTransformationRotY)
{
  TestUtils::testFindTransformationAxisRot<rotation3dy<double> >();
}

BOOST_AUTO_TEST_CASE(testFindTransformationRotZ)
{
  TestUtils::testFindTransformationAxisRot<rotation3dz<double> >();
}

BOOST_AUTO_TEST_SUITE_END()
