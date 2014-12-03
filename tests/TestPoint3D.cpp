//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "TestPoint3D.h"

#include "minimath/point3d.hpp"
#include "minimath/point3d_ops.hpp"
#include "minimath/numeric_utils.hpp" // for fp comparisons
#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>

void TestPoint3D::Setup()
{
  EPS = std::numeric_limits<minimath::pointxyzd::value_type>::epsilon();
}


void TestPoint3D::testInstantiation()
{
  minimath::pointxyzd pd1;
  minimath::pointxyzd pd2(1,2,3);
}

void TestPoint3D::testEquality()
{
  CPPUNIT_ASSERT(minimath::pointxyzd()==minimath::pointxyzd());
  minimath::pointxyzd pd1(1, 2, 3);
  minimath::pointxyzd pd2(1,2,3);
  CPPUNIT_ASSERT( pd1 == pd2);
}

void TestPoint3D::testInequality()
{
  minimath::pointxyzd pd1(10, 20, 30);
  minimath::pointxyzd pd2(1,2,3);
  CPPUNIT_ASSERT( pd1 != pd2);
}

void TestPoint3D::testCloseInequality()
{
  minimath::pointxyzd pd1(10, 20, 30);
  minimath::pointxyzd pd2(10.00001,20,30);
  CPPUNIT_ASSERT( pd1 != pd2);
}

void TestPoint3D::testAccessX()
{
  minimath::pointxyzd pd1(10, 20, 30);
  CPPUNIT_ASSERT( minimath::compare_with_tolerance(pd1.x(), 10., EPS));
}

void TestPoint3D::testAccessY()
{
  minimath::pointxyzd pd1(10, 20, 30);
  CPPUNIT_ASSERT( minimath::compare_with_tolerance(pd1.y(), 20., EPS) );
}

void TestPoint3D::testAccessZ()
{
  minimath::pointxyzd pd1(10, 20, 30);
  CPPUNIT_ASSERT( minimath::compare_with_tolerance(pd1.z(), 30., EPS) );
}

void TestPoint3D::testSetX()
{
  minimath::pointxyzd pd1;
  pd1.x(3.14);
  CPPUNIT_ASSERT( minimath::compare_with_tolerance(pd1.x(), 3.14, EPS) );
}

void TestPoint3D::testSetY()
{
  minimath::pointxyzd pd1;
  pd1.y(3.14);
  CPPUNIT_ASSERT(  minimath::compare_with_tolerance(pd1.y(), 3.14, EPS) );
}

void TestPoint3D::testSetZ()
{
  minimath::pointxyzd pd1;
  pd1.z(3.14);
  CPPUNIT_ASSERT(  minimath::compare_with_tolerance(pd1.z(), 3.14, EPS) );
}

void TestPoint3D::testCopyConstruction()
{
  minimath::pointxyzd pd1(1,2,3);
  minimath::pointxyzd pd2 = pd1;
  CPPUNIT_ASSERT( pd1 == pd2);
}

void TestPoint3D::testAssignment()  {
  minimath::pointxyzd pd1(1,2,3);
  minimath::pointxyzd pd2;
  pd2 = pd1;
  CPPUNIT_ASSERT( pd1 == pd2);
}

void TestPoint3D::testPlusEquals()
{
  minimath::pointxyzd pd(1, 2, 3);
  pd += minimath::pointxyzd(10,20,30);
  CPPUNIT_ASSERT( pd == minimath::pointxyzd(11,22,33));
}

void TestPoint3D::testMinusEquals()
{
  minimath::pointxyzd pd(11, 22, 33);
  pd -= minimath::pointxyzd(10,20,30);
  CPPUNIT_ASSERT( pd == minimath::pointxyzd(1,2,3));
}

void TestPoint3D::testTimesEqualsScalar()
{
  minimath::pointxyzd pd(1, 2, 3);
  pd *= 11;
  CPPUNIT_ASSERT( pd == minimath::pointxyzd(11,22,33));

}

void TestPoint3D::testDivideEqualsScalar()
{
  minimath::pointxyzd pd(100, 200, 300);
  pd /= 10;
  CPPUNIT_ASSERT( pd == minimath::pointxyzd(10,20,30));
}

void TestPoint3D::testTimesScalar()
{
  minimath::pointxyzd pd = minimath::pointxyzd(1, 2, 3) * 11;
  CPPUNIT_ASSERT( pd == minimath::pointxyzd(11,22,33));

}

void TestPoint3D::testDivideScalar()
{
  minimath::pointxyzd pd = minimath::pointxyzd(100, 200, 300)/10;
  CPPUNIT_ASSERT( pd == minimath::pointxyzd(10,20,30));
}


void TestPoint3D::testMagnitudeSquared()
{
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::mag2(minimath::pointxyzd(1,1,1)), 3., EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::mag2(minimath::pointxyzd(5,5,5)), 75., EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::mag2(minimath::pointxyzd(5,0,0)), 25., EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::mag2(minimath::pointxyzd(0,5,0)), 25., EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::mag2(minimath::pointxyzd(0,0,5)), 25., EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::mag2(minimath::pointxyzd(-5,0,5)), 50., EPS));
}

void TestPoint3D::testDistanceSquared()
{
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,1,1),
                                                        minimath::pointxyzd(1,1,1)), 0., EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,1,1),
                                                        minimath::pointxyzd(0,0,0)), 3., EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,1,0),
                                                        minimath::pointxyzd(0,0,0)), 2., EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,0,1),
                                                        minimath::pointxyzd(0,0,0)), 2., EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,0,0),
                                                        minimath::pointxyzd(0,0,0)), 1., EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(0,1,0),
                                                        minimath::pointxyzd(0,0,0)), 1., EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(0,0,1),
                                                        minimath::pointxyzd(0,0,0)), 1., EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,0,0),
                                                        minimath::pointxyzd(-1,0,0)), 4., EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,1,1),
                                                        minimath::pointxyzd(-1,-1,-1)), 12., EPS));
}

void TestPoint3D::testDotProduct()
{
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(3., minimath::dot(minimath::pointxyzd(1,1,1),
                                                          minimath::pointxyzd(1,1,1)), EPS));
  // parallel opposite direction
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(-3., minimath::dot(minimath::pointxyzd(1,1,1),
                                                           minimath::pointxyzd(-1,-1,-1)), EPS));
  // orthoginal
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(0., minimath::dot(minimath::pointxyzd(1,0,0),
                                                          minimath::pointxyzd(0,1,0)), EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(0., minimath::dot(minimath::pointxyzd(1,0,0),
                                                          minimath::pointxyzd(0,0,1)), EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(0., minimath::dot(minimath::pointxyzd(0,1,0),
                                                          minimath::pointxyzd(1,0,0)), EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(0., minimath::dot(minimath::pointxyzd(0,1,0),
                                                          minimath::pointxyzd(0,0,1)), EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(0., minimath::dot(minimath::pointxyzd(0,0,1),
                                                          minimath::pointxyzd(1,0,0)), EPS));
  CPPUNIT_ASSERT(minimath::compare_with_tolerance(0., minimath::dot(minimath::pointxyzd(0,0,1),
                                                          minimath::pointxyzd(0,1,0)), EPS));
}

namespace
{
void test_normalize_non_member(int i, int j, int k)
{
  using namespace minimath;
  for (int n = 0; n < 100; ++n)
  {
    pointxyzd p(i*std::rand(), j*std::rand(), k*std::rand());
    pointxyzd::value_type d = std::sqrt(mag2(p));
    pointxyzd::value_type EPS = std::numeric_limits<minimath::pointxyzd::value_type>::epsilon();
    p = normalize(p);
    d = mag2(p);
    CPPUNIT_ASSERT(compare_with_tolerance(d, pointxyzd::value_type(1.), 5.0e-16));
  }
}
void test_normalize(int i, int j, int k)
{
  using namespace minimath;
  for (int n = 0; n < 100; ++n)
  {
    pointxyzd p(i*std::rand(), j*std::rand(), k*std::rand());
    pointxyzd::value_type d = std::sqrt(mag2(p));
    pointxyzd::value_type EPS = std::numeric_limits<minimath::pointxyzd::value_type>::epsilon();
    CPPUNIT_ASSERT(compare_with_tolerance(p.normalize(), d, EPS));
    std::stringstream ss;
    ss << "mag2(p) -1 = " << mag2(p) - pointxyzd::value_type(1.);
    ss << " EPS " << EPS;
    d = mag2(p);
    CPPUNIT_ASSERT_MESSAGE(ss.str().c_str(), compare_with_tolerance(d, pointxyzd::value_type(1.), 5.0e-16));
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
