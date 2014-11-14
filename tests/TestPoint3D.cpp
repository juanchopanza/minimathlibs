//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "TestPoint3D.h"

#include "Math/Point3D.h"
#include "Math/Point3DOps.h"
#include "Math/Utils.h" // for FP comparisons
#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>

void TestPoint3D::Setup()
{
  EPS = std::numeric_limits<Math::PointXYZD::value_type>::epsilon();
}


void TestPoint3D::testInstantiation()
{
  Math::PointXYZD pd1;
  Math::PointXYZD pd2(1,2,3);
}

void TestPoint3D::testEquality()
{
  CPPUNIT_ASSERT(Math::PointXYZD()==Math::PointXYZD());
  Math::PointXYZD pd1(1, 2, 3);
  Math::PointXYZD pd2(1,2,3);
  CPPUNIT_ASSERT( pd1 == pd2);
}

void TestPoint3D::testInequality()
{
  Math::PointXYZD pd1(10, 20, 30);
  Math::PointXYZD pd2(1,2,3);
  CPPUNIT_ASSERT( pd1 != pd2);
}

void TestPoint3D::testCloseInequality()
{
  Math::PointXYZD pd1(10, 20, 30);
  Math::PointXYZD pd2(10.00001,20,30);
  CPPUNIT_ASSERT( pd1 != pd2);
}

void TestPoint3D::testAccessX()
{
  Math::PointXYZD pd1(10, 20, 30);
  CPPUNIT_ASSERT( Math::compareWithTolerance(pd1.x(), 10., EPS));
}

void TestPoint3D::testAccessY()
{
  Math::PointXYZD pd1(10, 20, 30);
  CPPUNIT_ASSERT( Math::compareWithTolerance(pd1.y(), 20., EPS) );
}

void TestPoint3D::testAccessZ()
{
  Math::PointXYZD pd1(10, 20, 30);
  CPPUNIT_ASSERT( Math::compareWithTolerance(pd1.z(), 30., EPS) );
}

void TestPoint3D::testSetX()
{
  Math::PointXYZD pd1;
  pd1.x(3.14);
  CPPUNIT_ASSERT( Math::compareWithTolerance(pd1.x(), 3.14, EPS) );
}

void TestPoint3D::testSetY()
{
  Math::PointXYZD pd1;
  pd1.y(3.14);
  CPPUNIT_ASSERT(  Math::compareWithTolerance(pd1.y(), 3.14, EPS) );
}

void TestPoint3D::testSetZ()
{
  Math::PointXYZD pd1;
  pd1.z(3.14);
  CPPUNIT_ASSERT(  Math::compareWithTolerance(pd1.z(), 3.14, EPS) );
}

void TestPoint3D::testCopyConstruction()
{
  Math::PointXYZD pd1(1,2,3);
  Math::PointXYZD pd2 = pd1;
  CPPUNIT_ASSERT( pd1 == pd2);
}

void TestPoint3D::testAssignment()  {
  Math::PointXYZD pd1(1,2,3);
  Math::PointXYZD pd2;
  pd2 = pd1;
  CPPUNIT_ASSERT( pd1 == pd2);
}

void TestPoint3D::testPlusEquals()
{
  Math::PointXYZD pd(1, 2, 3);
  pd += Math::PointXYZD(10,20,30);
  CPPUNIT_ASSERT( pd == Math::PointXYZD(11,22,33));
}

void TestPoint3D::testMinusEquals()
{
  Math::PointXYZD pd(11, 22, 33);
  pd -= Math::PointXYZD(10,20,30);
  CPPUNIT_ASSERT( pd == Math::PointXYZD(1,2,3));
}

void TestPoint3D::testTimesEqualsScalar()
{
  Math::PointXYZD pd(1, 2, 3);
  pd *= 11;
  CPPUNIT_ASSERT( pd == Math::PointXYZD(11,22,33));

}

void TestPoint3D::testDivideEqualsScalar()
{
  Math::PointXYZD pd(100, 200, 300);
  pd /= 10;
  CPPUNIT_ASSERT( pd == Math::PointXYZD(10,20,30));
}

void TestPoint3D::testTimesScalar()
{
  Math::PointXYZD pd = Math::PointXYZD(1, 2, 3) * 11;
  CPPUNIT_ASSERT( pd == Math::PointXYZD(11,22,33));

}

void TestPoint3D::testDivideScalar()
{
  Math::PointXYZD pd = Math::PointXYZD(100, 200, 300)/10;
  CPPUNIT_ASSERT( pd == Math::PointXYZD(10,20,30));
}


void TestPoint3D::testMagnitudeSquared()
{
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::mag2(Math::PointXYZD(1,1,1)), 3., EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::mag2(Math::PointXYZD(5,5,5)), 75., EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::mag2(Math::PointXYZD(5,0,0)), 25., EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::mag2(Math::PointXYZD(0,5,0)), 25., EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::mag2(Math::PointXYZD(0,0,5)), 25., EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::mag2(Math::PointXYZD(-5,0,5)), 50., EPS));
}

void TestPoint3D::testDistanceSquared()
{
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::dist2(Math::PointXYZD(1,1,1),
                                                        Math::PointXYZD(1,1,1)), 0., EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::dist2(Math::PointXYZD(1,1,1),
                                                        Math::PointXYZD(0,0,0)), 3., EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::dist2(Math::PointXYZD(1,1,0),
                                                        Math::PointXYZD(0,0,0)), 2., EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::dist2(Math::PointXYZD(1,0,1),
                                                        Math::PointXYZD(0,0,0)), 2., EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::dist2(Math::PointXYZD(1,0,0),
                                                        Math::PointXYZD(0,0,0)), 1., EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::dist2(Math::PointXYZD(0,1,0),
                                                        Math::PointXYZD(0,0,0)), 1., EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::dist2(Math::PointXYZD(0,0,1),
                                                        Math::PointXYZD(0,0,0)), 1., EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::dist2(Math::PointXYZD(1,0,0),
                                                        Math::PointXYZD(-1,0,0)), 4., EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(Math::dist2(Math::PointXYZD(1,1,1),
                                                        Math::PointXYZD(-1,-1,-1)), 12., EPS));
}

void TestPoint3D::testDotProduct()
{
  CPPUNIT_ASSERT(Math::compareWithTolerance(3., Math::dot(Math::PointXYZD(1,1,1),
                                                          Math::PointXYZD(1,1,1)), EPS));
  // parallel opposite direction
  CPPUNIT_ASSERT(Math::compareWithTolerance(-3., Math::dot(Math::PointXYZD(1,1,1),
                                                           Math::PointXYZD(-1,-1,-1)), EPS));
  // orthoginal
  CPPUNIT_ASSERT(Math::compareWithTolerance(0., Math::dot(Math::PointXYZD(1,0,0),
                                                          Math::PointXYZD(0,1,0)), EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(0., Math::dot(Math::PointXYZD(1,0,0),
                                                          Math::PointXYZD(0,0,1)), EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(0., Math::dot(Math::PointXYZD(0,1,0),
                                                          Math::PointXYZD(1,0,0)), EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(0., Math::dot(Math::PointXYZD(0,1,0),
                                                          Math::PointXYZD(0,0,1)), EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(0., Math::dot(Math::PointXYZD(0,0,1),
                                                          Math::PointXYZD(1,0,0)), EPS));
  CPPUNIT_ASSERT(Math::compareWithTolerance(0., Math::dot(Math::PointXYZD(0,0,1),
                                                          Math::PointXYZD(0,1,0)), EPS));
}

namespace
{
void test_normalize_non_member(int i, int j, int k)
{
  using namespace Math;
  for (int n = 0; n < 100; ++n)
  {
    PointXYZD p(i*std::rand(), j*std::rand(), k*std::rand());
    PointXYZD::value_type d = std::sqrt(mag2(p));
    PointXYZD::value_type EPS = std::numeric_limits<Math::PointXYZD::value_type>::epsilon();
    p = normalize(p);
    d = mag2(p);
    CPPUNIT_ASSERT(compareWithTolerance(d, PointXYZD::value_type(1.), 5.0e-16));
  }
}
void test_normalize(int i, int j, int k)
{
  using namespace Math;
  for (int n = 0; n < 100; ++n)
  {
    PointXYZD p(i*std::rand(), j*std::rand(), k*std::rand());
    PointXYZD::value_type d = std::sqrt(mag2(p));
    PointXYZD::value_type EPS = std::numeric_limits<Math::PointXYZD::value_type>::epsilon();
    CPPUNIT_ASSERT(compareWithTolerance(p.normalize(), d, EPS));
    std::stringstream ss;
    ss << "mag2(p) -1 = " << mag2(p) - PointXYZD::value_type(1.);
    ss << " EPS " << EPS;
    d = mag2(p);
    CPPUNIT_ASSERT_MESSAGE(ss.str().c_str(), compareWithTolerance(d, PointXYZD::value_type(1.), 5.0e-16));
  }
}
}

void TestPoint3D::testNormalize()
{
    test_normalize(1, 1, 1);
    test_normalize(1, 1, -1);
    test_normalize(1, -1, 1);
    test_normalize(-1, 1, 1);
    test_normalize(1, -1, -1);
    test_normalize(-1, -1, 1);
    test_normalize(-1, 1, -1);
    test_normalize(-1, -1, -1);
}

void TestPoint3D::testNormalizeNonMember()
{
    test_normalize_non_member(1, 1, 1);
    test_normalize_non_member(1, 1, -1);
    test_normalize_non_member(1, -1, 1);
    test_normalize_non_member(-1, 1, 1);
    test_normalize_non_member(1, -1, -1);
    test_normalize_non_member(-1, -1, 1);
    test_normalize_non_member(-1, 1, -1);
    test_normalize_non_member(-1, -1, -1);
}
