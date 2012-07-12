//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimath.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//

#ifndef TESTS_ROTATION3D_H__
#define TESTS_ROTATION3D_H__

#include <iostream>
#include <cmath>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Rotation3D.h"
#include "Math/Point3D.h"

#include "Defines.h"

class TestRotation3D : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestRotation3D);
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

  CPPUNIT_TEST_SUITE_END();

 protected:

  void testInstantiation()
  {
    Rotation3D rot1, rot2;
  }
  void testDefaultEquality()
  {
    CPPUNIT_ASSERT(Rotation3D() == Rotation3D());
  }
  void testCopyConstruction()
  {
    Rotation3D rot1;
    Rotation3D rot2(rot1);
    CPPUNIT_ASSERT(rot1 == rot2);
  }

  void testAssignment()
  {
    Rotation3D rot1, rot2;
    rot2 = rot1;
    CPPUNIT_ASSERT(rot1 == rot2);
  }

  void testNullRotation()
  {
    Rotation3D rot;
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

  void testRotatePoint45X()
  {
    Rotation3D rot = Rotation3DX(PI/4.); // 45 degree rotation about X
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., cos45, cos45));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -cos45, cos45));
  }

  void testRotatePoint90X()
  {
    Rotation3D rot = Rotation3DX(PI/2.); // 90 degree rotation about X
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));
  }

  void testRotatePoint180X()
  {
    Rotation3D rot = Rotation3DX(PI); // 180 degree rotation about X

    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
  }

  void testRotatePoint45Y()
  {
    Rotation3D rot = Rotation3DY(PI/4.); // 45 degree rotation about X
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0., -cos45));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0, cos45));
  }

  void testRotatePoint90Y()
  {
    Rotation3D rot = Rotation3DY(PI/2.); // 90 degree rotation about X
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));
  }

  void testRotatePoint180Y()
  {
    Rotation3D rot = Rotation3DY(PI); // 180 degree rotation about X

    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
  }

  void testRotatePoint45Z()
  {
    Rotation3D rot = Rotation3DZ(PI/4.); // 45 degree rotation about Z
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, cos45, 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(-cos45, cos45, 0));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0, 0, 1));
  }

  void testRotatePoint90Z()
  {
    Rotation3D rot = Rotation3DZ(PI/2.); // 90 degree rotation about Z
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

  void testRotatePoint180Z()
  {
    Rotation3D rot = Rotation3DZ(PI); // 180 degree rotation about Z

    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

};

#endif

