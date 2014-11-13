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
#include "TestRotation3DZ.h"
#include "TestRotation3DUtils.h"

using namespace Math;

void TestRotation3DZ::testInstantiation()
{
  Rotation3DZ<double> rot1, rot2;
}

void TestRotation3DZ::testDefaultEquality()
{
  CPPUNIT_ASSERT(Rotation3DZ<double>() == Rotation3DZ<double>());
}

void TestRotation3DZ::testCopyConstruction()
{
  Rotation3DZ<double> rot1;
  Rotation3DZ<double> rot2(rot1);
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3DZ::testAssignment()
{
  Rotation3DZ<double> rot1, rot2;
  rot2 = rot1;
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestRotation3DZ::testRotatePoint0()
{
  Rotation3DZ<double> rotx4(0);
  PointXYZD pTest = rotx4*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = rotx4*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = rotx4*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestRotation3DZ::testRotatePoint45()
{
  Rotation3DZ<double> rotx6(PI/4.); // 45 degree rotation about Z
  PointXYZD pTest = rotx6*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, cos45, 0.));

  pTest = rotx6*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(-cos45, cos45, 0));

  pTest = rotx6*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0, 0, 1));
}

void TestRotation3DZ::testRotatePoint90()
{
  Rotation3DZ<double> rotx4(PI/2.); // 90 degree rotation about Z
  PointXYZD pTest = rotx4*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = rotx4*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = rotx4*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestRotation3DZ::testRotatePoint180()
{
  Rotation3DZ<double> rotx5(PI); // 180 degree rotation about Z

  PointXYZD pTest = rotx5*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = rotx5*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

  pTest = rotx5*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestRotation3DZ::testInverse()
{
  CPPUNIT_ASSERT(TestUtils::testInverse<Rotation3DZ<double> >());
}

void TestRotation3DZ::testInvert()
{
  CPPUNIT_ASSERT(TestUtils::testInvert<Rotation3DZ<double> >());
}

