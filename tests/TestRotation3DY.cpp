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
#include "TestRotation3DUtils.h"
#include "TestRotation3DY.h"

using namespace minimath;

void TestRotation3DY::testInstantiation()
{
  rotation3dy<double> rot1, rot2;
}
void TestRotation3DY::testDefaultEquality()
{
  CPPUNIT_ASSERT(rotation3dy<double>() == rotation3dy<double>());
}
void TestRotation3DY::testCopyConstruction()
{
  rotation3dy<double> rot1;
  rotation3dy<double> rot2(rot1);
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3DY::testAssignment()
{
  rotation3dy<double> rot1, rot2;
  rot2 = rot1;
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3DY::testRotatePoint0()
{
  rotation3dy<double> rotx4(0);
  pointxyzd pTest = rotx4*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));

  pTest = rotx4*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rotx4*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., 1.));
}

void TestRotation3DY::testRotatePoint45()
{
  rotation3dy<double> rotx6(PI/4.); // 45 degree rotation about X
  pointxyzd pTest = rotx6*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(cos45, 0., -cos45));

  pTest = rotx6*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0));

  pTest = rotx6*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(cos45, 0, cos45));
}

void TestRotation3DY::testRotatePoint90()
{
  rotation3dy<double> rotx4(PI/2.); // 90 degree rotation about X
  pointxyzd pTest = rotx4*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., -1.));

  pTest = rotx4*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rotx4*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(1., 0., 0.));
}

void TestRotation3DY::testRotatePoint180()
{
  rotation3dy<double> rotx5(PI); // 180 degree rotation about X

  pointxyzd pTest = rotx5*p100;
  CPPUNIT_ASSERT(pTest == pointxyzd(-1., 0., 0.));

  pTest = rotx5*p010;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 1., 0.));

  pTest = rotx5*p001;
  CPPUNIT_ASSERT(pTest == pointxyzd(0., 0., -1.));
}

void TestRotation3DY::testInverse()
{
  CPPUNIT_ASSERT(TestUtils::testInverse<rotation3dy<double> >());
}

void TestRotation3DY::testInvert()
{
  CPPUNIT_ASSERT(TestUtils::testInvert<rotation3dy<double> >());
}
