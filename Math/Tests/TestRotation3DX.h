//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_TESTROTATION3DX_H__
#define TESTS_TESTROTATION3DX_H__

#include <iostream>
#include <cmath>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Rotation3D.h"
#include "Math/Point3D.h"

#include "Defines.h"
#include "TestRotation3DUtils.h"

using namespace Math;

class TestRotation3DX : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestRotation3DX);
  CPPUNIT_TEST(testInstantiation);
  CPPUNIT_TEST(testDefaultEquality);
  CPPUNIT_TEST(testCopyConstruction);
  CPPUNIT_TEST(testAssignment);
  CPPUNIT_TEST(testRotatePoint0);
  CPPUNIT_TEST(testRotatePoint45);
  CPPUNIT_TEST(testRotatePoint90);
  CPPUNIT_TEST(testRotatePoint180);
  CPPUNIT_TEST(testInverse);
  CPPUNIT_TEST(testInvert);
  CPPUNIT_TEST_SUITE_END();

 protected:

  void testInstantiation()
  {
    Rotation3DX<double> rot1, rot2;
  }
  void testDefaultEquality()
  {
    CPPUNIT_ASSERT(Rotation3DX<double>() == Rotation3DX<double>());
  }
  void testCopyConstruction()
  {
    Rotation3DX<double> rot1;
    Rotation3DX<double> rot2(rot1);
    CPPUNIT_ASSERT(rot1 == rot2);
  }

  void testAssignment()
  {
    Rotation3DX<double> rot1, rot2;
    rot2 = rot1;
    CPPUNIT_ASSERT(rot1 == rot2);
  }

  void testRotatePoint0()
  {
    Rotation3DX<double> rotx4(0);
    PointXYZD pTest = rotx4*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rotx4*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = rotx4*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

  void testRotatePoint45()
  {
    Rotation3DX<double> rotx6(PI/4.); // 45 degree rotation about X
    PointXYZD pTest = rotx6*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rotx6*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., cos45, cos45));

    pTest = rotx6*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -cos45, cos45));
  }

  void testRotatePoint90()
  {
    Rotation3DX<double> rotx4(PI/2.); // 90 degree rotation about X
    PointXYZD pTest = rotx4*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rotx4*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));

    pTest = rotx4*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));
  }

  void testRotatePoint180()
  {
    Rotation3DX<double> rotx5(PI); // 180 degree rotation about X

    PointXYZD pTest = rotx5*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rotx5*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

    pTest = rotx5*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
  }

  void testInverse()
  {
    CPPUNIT_ASSERT(TestUtils::testInverse<Rotation3DX<double> >());
  }

  void testInvert()
  {
    CPPUNIT_ASSERT(TestUtils::testInvert<Rotation3DX<double> >());
  }

};

#endif

