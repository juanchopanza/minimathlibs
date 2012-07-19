//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_TESTAXISANGLE_H__
#define TESTS_TESTAXISANGLE_H__

#include <iostream>
#include <cmath>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Rotation3D.h"
#include "Math/Point3D.h"

#include "Defines.h"

class TestAxisAngle : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestAxisAngle);
  CPPUNIT_TEST(testInstantiation);
  CPPUNIT_TEST(testDefaultEquality);
  CPPUNIT_TEST(testCopyConstruction);
  CPPUNIT_TEST(testAssignment);
  CPPUNIT_TEST(testNullRotation);
  CPPUNIT_TEST(testRotatePoint45X);
  CPPUNIT_TEST(testRotatePoint90X);
  CPPUNIT_TEST(testRotatePoint180X);
  CPPUNIT_TEST(testRotatePoint45Y);
  CPPUNIT_TEST(testRotatePoint90Y);
  CPPUNIT_TEST(testRotatePoint180Y);
  CPPUNIT_TEST(testRotatePoint45Z);
  CPPUNIT_TEST(testRotatePoint90Z);
  CPPUNIT_TEST(testRotatePoint180Z);
  CPPUNIT_TEST(testAssignRotation3DX);
  CPPUNIT_TEST(testAssignRotation3DY);
  CPPUNIT_TEST(testAssignRotation3DZ);
  CPPUNIT_TEST(testInverse);
  CPPUNIT_TEST(testInvert);
  CPPUNIT_TEST_SUITE_END();

 protected:

  void testInstantiation()
  {
    AxisAngle rot1, rot2;
  }
  void testDefaultEquality()
  {
    CPPUNIT_ASSERT(AxisAngle() == AxisAngle());
  }
  void testCopyConstruction()
  {
    AxisAngle rot1;
    AxisAngle rot2(rot1);
    CPPUNIT_ASSERT(rot1 == rot2);
  }

  void testAssignment()
  {
    AxisAngle rot1, rot2;
    rot2 = rot1;
    CPPUNIT_ASSERT(rot1 == rot2);
  }

  void testNullRotation()
  {
    AxisAngle rot;
    PointXYZD pTest = Rotation3D(rot)*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = Rotation3D(rot)*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = Rotation3D(rot)*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

  void testRotatePoint45X()
  {
    AxisAngle rot(p100, PI/4.); // 45 degree rotation about X
    PointXYZD pTest = Rotation3D(rot)*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = Rotation3D(rot)*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., cos45, cos45));

    pTest = Rotation3D(rot)*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -cos45, cos45));
  }

  void testRotatePoint90X()
  {
    AxisAngle rot(p100, PI/2.); // 90 degree rotation about X
    PointXYZD pTest = Rotation3D(rot)*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = Rotation3D(rot)*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));

    pTest = Rotation3D(rot)*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));
  }

  void testRotatePoint180X()
  {
    AxisAngle rot(p100, PI); // 180 degree rotation about X

    PointXYZD pTest = Rotation3D(rot)*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = Rotation3D(rot)*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

    pTest = Rotation3D(rot)*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
  }

  void testRotatePoint45Y()
  {
    AxisAngle rot(p010, PI/4.); // 45 degree rotation about Y
    PointXYZD pTest = Rotation3D(rot)*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0., -cos45));

    pTest = Rotation3D(rot)*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0));

    pTest = Rotation3D(rot)*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0, cos45));
  }

  void testRotatePoint90Y()
  {
    AxisAngle rot(p010, PI/2.); // 90 degree rotation about Y
    PointXYZD pTest = Rotation3D(rot)*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));

    pTest = Rotation3D(rot)*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = Rotation3D(rot)*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));
  }

  void testRotatePoint180Y()
  {
    AxisAngle rot(p010, PI); // 180 degree rotation about Y

    PointXYZD pTest = Rotation3D(rot)*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = Rotation3D(rot)*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = Rotation3D(rot)*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
  }

  void testRotatePoint45Z()
  {
    AxisAngle rot(p001, PI/4.); // 45 degree rotation about Z
    PointXYZD pTest = Rotation3D(rot)*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, cos45, 0.));

    pTest = Rotation3D(rot)*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(-cos45, cos45, 0));

    pTest = Rotation3D(rot)*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0, 0, 1));
  }

  void testRotatePoint90Z()
  {
    AxisAngle rot(p001, PI/2.); // 90 degree rotation about Z
    PointXYZD pTest = Rotation3D(rot)*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = Rotation3D(rot)*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = Rotation3D(rot)*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

  void testRotatePoint180Z()
  {
    AxisAngle rot(p001, PI); // 180 degree rotation about Z

    PointXYZD pTest = Rotation3D(rot)*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = Rotation3D(rot)*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

    pTest = Rotation3D(rot)*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

  void testAssignRotation3DX()
  {
    for (int i = 1; i < 9; ++i) {
      CPPUNIT_ASSERT(AxisAngle(p100, PI/i) == Rotation3DX(PI/i));
    }
  }

  void testAssignRotation3DY()
  {
    for (int i = 1; i < 9; ++i) {
      CPPUNIT_ASSERT(AxisAngle(p010, PI/i) == Rotation3DY(PI/i));
    }
  }


  void testAssignRotation3DZ()
  {
     for (int i = 1; i < 9; ++i) {
      CPPUNIT_ASSERT(AxisAngle(p001, PI/i) == Rotation3DZ(PI/i));
    }
  }

  void testInverse()
  {
    CPPUNIT_ASSERT(TestUtils::testInverseAxisAngle(p100));
    CPPUNIT_ASSERT(TestUtils::testInverseAxisAngle(p010));
    CPPUNIT_ASSERT(TestUtils::testInverseAxisAngle(p001));
  }

  void testInvert()
  {
    CPPUNIT_ASSERT(TestUtils::testInvertAxisAngle(p100));
    CPPUNIT_ASSERT(TestUtils::testInvertAxisAngle(p010));
    CPPUNIT_ASSERT(TestUtils::testInvertAxisAngle(p001));
  }

};

#endif

