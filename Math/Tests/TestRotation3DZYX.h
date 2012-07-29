//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
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

namespace
{

//
// Check that a RotationZYX defined by angles phi, theta, psi has the same
// effect on a point as individual Z, Y and X rotations.
//
bool testRotationZYX(const Math::PointXYZD& point,
                     double phi, 
                     double theta, 
                     double psi)
{ 
  Rotation3DZYX<double> rot1(phi, theta, psi);
  PointXYZD ref = Rotation3DX<double>(psi) *
                  ( Rotation3DY<double>(theta) * (Rotation3DZ<double>(phi)*point) );
  return rot1*point == ref;
}

}

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
  CPPUNIT_TEST(testZYXRotations);
  CPPUNIT_TEST(testInverse);
  CPPUNIT_TEST(testInvert);
  CPPUNIT_TEST_SUITE_END();

 protected:

  void testInstantiation()
  {
    Rotation3DZYX<double> rot1, rot2;
  }
  void testDefaultEquality()
  {
    CPPUNIT_ASSERT(Rotation3DZYX<double>() == Rotation3DZYX<double>());
  }
  void testCopyConstruction()
  {
    Rotation3DZYX<double> rot1;
    Rotation3DZYX<double> rot2(rot1);
    CPPUNIT_ASSERT(rot1 == rot2);
  }

  void testAssignment()
  {
    Rotation3DZYX<double> rot1, rot2;
    rot2 = rot1;
    CPPUNIT_ASSERT(rot1 == rot2);
  }

  void testNullRotation()
  {
    Rotation3DZYX<double> rot;
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

  void testRotatePoint45X()
  {
    Rotation3DZYX<double> rot(0, 0, PI/4.); // 45 degree rotation about X
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., cos45, cos45));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -cos45, cos45));
  }

  void testRotatePoint90X()
  {
    Rotation3DZYX<double> rot(0, 0, PI/2.); // 90 degree rotation about X
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));
  }

  void testRotatePoint180X()
  {
    Rotation3DZYX<double> rot(0, 0, PI); // 180 degree rotation about X

    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
  }

  void testRotatePoint45Y()
  {
    Rotation3DZYX<double> rot(0, PI/4., 0); // 45 degree rotation about X
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0., -cos45));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0, cos45));
  }

  void testRotatePoint90Y()
  {
    Rotation3DZYX<double> rot(0, PI/2., 0); // 90 degree rotation about X
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));
  }

  void testRotatePoint180Y()
  {
    Rotation3DZYX<double> rot(0, PI, 0); // 180 degree rotation about X

    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
  }

  void testRotatePoint45Z()
  {
    Rotation3DZYX<double> rot(PI/4., 0, 0); // 45 degree rotation about Z
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, cos45, 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(-cos45, cos45, 0));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0, 0, 1));
  }

  void testRotatePoint90Z()
  {
    Rotation3DZYX<double> rot(PI/2., 0, 0); // 90 degree rotation about Z
    PointXYZD pTest = rot*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = rot*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = rot*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

  void testRotatePoint180Z()
  {
    Rotation3DZYX<double> rot(PI, 0, 0); // 180 degree rotation about Z

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
      CPPUNIT_ASSERT(Rotation3DZYX<double>(0, 0, PI/i) == Rotation3DX<double>(PI/i));
    }
  }

  void testAssignRotation3DY()
  {
    for (int i = 1; i < 9; ++i) {
      CPPUNIT_ASSERT(Rotation3DZYX<double>(0, PI/i, 0) == Rotation3DY<double>(PI/i));
    }
  }


  void testAssignRotation3DZ()
  {
     for (int i = 1; i < 9; ++i) {
      CPPUNIT_ASSERT(Rotation3DZYX<double>(PI/i, 0, 0) == Rotation3DZ<double>(PI/i));
    }
  }

  void testZYXRotations()
  {
    for (int i = 1; i < 9; ++i) {
 
      const double angle = PI/i;
 
      CPPUNIT_ASSERT(testRotationZYX(p100, angle, angle, angle));
      CPPUNIT_ASSERT(testRotationZYX(p010, angle, angle, angle));
      CPPUNIT_ASSERT(testRotationZYX(p001, angle, angle, angle)); 

      CPPUNIT_ASSERT(testRotationZYX(p100, -angle, angle, angle));
      CPPUNIT_ASSERT(testRotationZYX(p010, angle, angle, angle));
      CPPUNIT_ASSERT(testRotationZYX(p001, angle, angle, angle)); 

      CPPUNIT_ASSERT(testRotationZYX(p100, angle, angle, angle));
      CPPUNIT_ASSERT(testRotationZYX(p010, -angle, angle, angle));
      CPPUNIT_ASSERT(testRotationZYX(p001, angle, angle, angle)); 

      CPPUNIT_ASSERT(testRotationZYX(p100, angle, -angle, angle));
      CPPUNIT_ASSERT(testRotationZYX(p010, angle, -angle, angle));
      CPPUNIT_ASSERT(testRotationZYX(p001, angle, -angle, angle)); 

      CPPUNIT_ASSERT(testRotationZYX(p100, -angle, -angle, -angle));
      CPPUNIT_ASSERT(testRotationZYX(p010, -angle, -angle, -angle));
      CPPUNIT_ASSERT(testRotationZYX(p001, -angle, -angle, -angle)); 

    }
  }

  void testInverse()
  {
    CPPUNIT_ASSERT(TestUtils::testInverseRotation3DZYX<Rotation3DX<double> >());
    CPPUNIT_ASSERT(TestUtils::testInverseRotation3DZYX<Rotation3DY<double> >());
    CPPUNIT_ASSERT(TestUtils::testInverseRotation3DZYX<Rotation3DZ<double> >());
  }

  void testInvert()
  {
    CPPUNIT_ASSERT(TestUtils::testInvertRotation3DZYX<Rotation3DX<double> >());
    CPPUNIT_ASSERT(TestUtils::testInvertRotation3DZYX<Rotation3DY<double> >());
    CPPUNIT_ASSERT(TestUtils::testInvertRotation3DZYX<Rotation3DZ<double> >());
  }

};

#endif

