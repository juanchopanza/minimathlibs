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

#include "minimath/rotation3d.hpp"
#include "minimath/point3d.hpp"

#include "Defines.h"
#include "TestRotation3DZYX.h"
#include "TestRotation3DUtils.h"

using namespace minimath;

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

void TestRotation3DZYX::testInstantiation()
{
  rotation3dzyx<double> rot1, rot2;
}

void TestRotation3DZYX::testDefaultEquality()
{
  CPPUNIT_ASSERT(rotation3dzyx<double>() == rotation3dzyx<double>());
}

void TestRotation3DZYX::testCopyConstruction()
{
  rotation3dzyx<double> rot1;
  rotation3dzyx<double> rot2(rot1);
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3DZYX::testAssignment()
{
  rotation3dzyx<double> rot1, rot2;
  rot2 = rot1;
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3DZYX::testNullRotation()
{
  rotation3dzyx<double> rot;
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., 1.));
}

void TestRotation3DZYX::testRotatePoint45X()
{
  rotation3dzyx<double> rot(0, 0, PI/4.); // 45 degree rotation about X
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., cos45, cos45));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., -cos45, cos45));
}

void TestRotation3DZYX::testRotatePoint90X()
{
  rotation3dzyx<double> rot(0, 0, PI/2.); // 90 degree rotation about X
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., 1.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., -1., 0.));
}

void TestRotation3DZYX::testRotatePoint180X()
{
  rotation3dzyx<double> rot(0, 0, PI); // 180 degree rotation about X

  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., -1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., -1.));
}

void TestRotation3DZYX::testRotatePoint45Y()
{
  rotation3dzyx<double> rot(0, PI/4., 0); // 45 degree rotation about X
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(cos45, 0., -cos45));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(cos45, 0, cos45));
}

void TestRotation3DZYX::testRotatePoint90Y()
{
  rotation3dzyx<double> rot(0, PI/2., 0); // 90 degree rotation about X
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., -1.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));
}

void TestRotation3DZYX::testRotatePoint180Y()
{
  rotation3dzyx<double> rot(0, PI, 0); // 180 degree rotation about X

  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(-1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., -1.));
}

void TestRotation3DZYX::testRotatePoint45Z()
{
  rotation3dzyx<double> rot(PI/4., 0, 0); // 45 degree rotation about Z
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(cos45, cos45, 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(-cos45, cos45, 0));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0, 0, 1));
}

void TestRotation3DZYX::testRotatePoint90Z()
{
  rotation3dzyx<double> rot(PI/2., 0, 0); // 90 degree rotation about Z
  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(-1., 0., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., 1.));
}

void TestRotation3DZYX::testRotatePoint180Z()
{
  rotation3dzyx<double> rot(PI, 0, 0); // 180 degree rotation about Z

  pointxyzd pTest = rot*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(-1., 0., 0.));

  pTest = rot*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., -1., 0.));

  pTest = rot*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., 1.));
}

void TestRotation3DZYX::testAssignRotation3DX()
{
  for (int i = 1; i < 9; ++i) {
    CPPUNIT_ASSERT(rotation3dzyx<double>(0, 0, PI/i) == rotation3dx<double>(PI/i));
  }
}

void TestRotation3DZYX::testAssignRotation3DY()
{
  for (int i = 1; i < 9; ++i) {
    CPPUNIT_ASSERT(rotation3dzyx<double>(0, PI/i, 0) == rotation3dy<double>(PI/i));
  }
}


void TestRotation3DZYX::testAssignRotation3DZ()
{
  for (int i = 1; i < 9; ++i) {
    CPPUNIT_ASSERT(rotation3dzyx<double>(PI/i, 0, 0) == rotation3dz<double>(PI/i));
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
  CPPUNIT_ASSERT(TestUtils::testInverseRotation3DZYX<rotation3dx<double> >());
  CPPUNIT_ASSERT(TestUtils::testInverseRotation3DZYX<rotation3dy<double> >());
  CPPUNIT_ASSERT(TestUtils::testInverseRotation3DZYX<rotation3dz<double> >());
}

void TestRotation3DZYX::testInvert()
{
  CPPUNIT_ASSERT(TestUtils::testInvertRotation3DZYX<rotation3dx<double> >());
  CPPUNIT_ASSERT(TestUtils::testInvertRotation3DZYX<rotation3dy<double> >());
  CPPUNIT_ASSERT(TestUtils::testInvertRotation3DZYX<rotation3dz<double> >());
}

