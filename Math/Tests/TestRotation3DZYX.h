//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//

#ifndef TESTS_TESTROTATION3DZYX_H__
#define TESTS_TESTROTATION3DZYX_H__

#include <iostream>
#include <cmath>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Rotation3D.h"
#include "Math/Point3D.h"

#include "Defines.h"

class TestRotation3DZYX : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestRotation3DZYX);
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

  CPPUNIT_TEST_SUITE_END();

 protected:

  void testInstantiation()
  {
    Rotation3DZYX rot1, rot2;
  }
  void testDefaultEquality()
  {
    CPPUNIT_ASSERT(Rotation3DZYX() == Rotation3DZYX());
  }
  void testCopyConstruction()
  {
    Rotation3DZYX rot1;
    Rotation3DZYX rot2(rot1);
    CPPUNIT_ASSERT(rot1 == rot2);
  }

  void testAssignment()
  {
    Rotation3DZYX rot1, rot2;
    rot2 = rot1;
    CPPUNIT_ASSERT(rot1 == rot2);
  }

  void testNullRotation()
  {
    Rotation3DZYX rot;
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

  void testRotatePoint45X()
  {
    Rotation3DZYX rot(0, 0, PI/4.); // 45 degree rotation about X
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., cos45, cos45));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -cos45, cos45));
  }

  void testRotatePoint90X()
  {
    Rotation3DZYX rot(0, 0, PI/2.); // 90 degree rotation about X
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));
  }

  void testRotatePoint180X()
  {
    Rotation3DZYX rot(0, 0, PI); // 180 degree rotation about X

    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
  }

  void testRotatePoint45Y()
  {
    Rotation3DZYX rot(0, PI/4., 0); // 45 degree rotation about X
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0., -cos45));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0, cos45));
  }

  void testRotatePoint90Y()
  {
    Rotation3DZYX rot(0, PI/2., 0); // 90 degree rotation about X
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));
  }

  void testRotatePoint180Y()
  {
    Rotation3DZYX rot(0, PI, 0); // 180 degree rotation about X

    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
  }

  void testRotatePoint45Z()
  {
    Rotation3DZYX rot(PI/4., 0, 0); // 45 degree rotation about Z
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, cos45, 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(-cos45, cos45, 0));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0, 0, 1));
  }

  void testRotatePoint90Z()
  {
    Rotation3DZYX rot(PI/2., 0, 0); // 90 degree rotation about Z
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

  void testRotatePoint180Z()
  {
    Rotation3DZYX rot(PI, 0, 0); // 180 degree rotation about Z

    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

  void testAssignRotation3DX()
  {
    for (int i = 1; i < 9; ++i) {
      CPPUNIT_ASSERT(Rotation3DZYX(0, 0, PI/i) == Rotation3DX(PI/i));
    }
  }

  void testAssignRotation3DY()
  {
    for (int i = 1; i < 9; ++i) {
      CPPUNIT_ASSERT(Rotation3DZYX(0, PI/i, 0) == Rotation3DY(PI/i));
    }
  }


  void testAssignRotation3DZ()
  {
     for (int i = 1; i < 9; ++i) {
      CPPUNIT_ASSERT(Rotation3DZYX(PI/i, 0, 0) == Rotation3DZ(PI/i));
    }
  }


};

#endif

