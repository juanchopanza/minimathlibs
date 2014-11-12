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

#include "Math/Rotation3D.h"
#include "Math/Point3D.h"

#include "Defines.h"
#include "TestRotationZYX.h"


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

} // namespace

void TestRotation3DZYX::testInstantiation()
{
  Rotation3DZYX<double> rot1, rot2;
}

void TestRotation3DZYX::testDefaultEquality()
{
  CPPUNIT_ASSERT(Rotation3DZYX<double>() == Rotation3DZYX<double>());
}

void TestRotation3DZYX::testCopyConstruction()
{
  Rotation3DZYX<double> rot1;
  Rotation3DZYX<double> rot2(rot1);
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3DZYX::testAssignment()
{
  Rotation3DZYX<double> rot1, rot2;
  rot2 = rot1;
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3DZYX::testNullRotation()
{
  Rotation3DZYX<double> rot;
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestRotation3DZYX::testRotatePoint45X()
{
  Rotation3DZYX<double> rot(0, 0, PI/4.); // 45 degree rotation about X
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., cos45, cos45));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -cos45, cos45));
}

void TestRotation3DZYX::testRotatePoint90X()
{
  Rotation3DZYX<double> rot(0, 0, PI/2.); // 90 degree rotation about X
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));
}

void TestRotation3DZYX::testRotatePoint180X()
{
  Rotation3DZYX<double> rot(0, 0, PI); // 180 degree rotation about X

  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
}

void TestRotation3DZYX::testRotatePoint45Y()
{
  Rotation3DZYX<double> rot(0, PI/4., 0); // 45 degree rotation about X
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0., -cos45));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0, cos45));
}

void TestRotation3DZYX::testRotatePoint90Y()
{
  Rotation3DZYX<double> rot(0, PI/2., 0); // 90 degree rotation about X
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));
}

void TestRotation3DZYX::testRotatePoint180Y()
{
  Rotation3DZYX<double> rot(0, PI, 0); // 180 degree rotation about X

  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
}

void TestRotation3DZYX::testRotatePoint45Z()
{
  Rotation3DZYX<double> rot(PI/4., 0, 0); // 45 degree rotation about Z
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, cos45, 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(-cos45, cos45, 0));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0, 0, 1));
}

void TestRotation3DZYX::testRotatePoint90Z()
{
  Rotation3DZYX<double> rot(PI/2., 0, 0); // 90 degree rotation about Z
  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestRotation3DZYX::testRotatePoint180Z()
{
  Rotation3DZYX<double> rot(PI, 0, 0); // 180 degree rotation about Z

  PointXYZD pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestRotation3DZYX::testAssignRotation3DX()
{
  for (int i = 1; i < 9; ++i) {
    CPPUNIT_ASSERT(Rotation3DZYX<double>(0, 0, PI/i) == Rotation3DX<double>(PI/i));
  }
}

void TestRotation3DZYX::testAssignRotation3DY()
{
  for (int i = 1; i < 9; ++i) {
    CPPUNIT_ASSERT(Rotation3DZYX<double>(0, PI/i, 0) == Rotation3DY<double>(PI/i));
  }
}


void TestRotation3DZYX::testAssignRotation3DZ()
{
  for (int i = 1; i < 9; ++i) {
    CPPUNIT_ASSERT(Rotation3DZYX<double>(PI/i, 0, 0) == Rotation3DZ<double>(PI/i));
  }
}

void TestRotation3DZYX::testZYXRotations()
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

void TestRotation3DZYX::testInverse()
{
  CPPUNIT_ASSERT(TestUtils::testInverseRotation3DZYX<Rotation3DX<double> >());
  CPPUNIT_ASSERT(TestUtils::testInverseRotation3DZYX<Rotation3DY<double> >());
  CPPUNIT_ASSERT(TestUtils::testInverseRotation3DZYX<Rotation3DZ<double> >());
}

void TestRotation3DZYX::testInvert()
{
  CPPUNIT_ASSERT(TestUtils::testInvertRotation3DZYX<Rotation3DX<double> >());
  CPPUNIT_ASSERT(TestUtils::testInvertRotation3DZYX<Rotation3DY<double> >());
  CPPUNIT_ASSERT(TestUtils::testInvertRotation3DZYX<Rotation3DZ<double> >());
}

