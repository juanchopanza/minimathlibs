//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestPoint3D
#include <boost/test/unit_test.hpp>
#include "minimath/point3d.hpp"
#include "minimath/point3d_ops.hpp"
#include "minimath/numeric_utils.hpp" // for fp comparisons
#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>

namespace
{
typedef minimath::pointxyzd::value_type scalar_type;
const scalar_type EPS = std::numeric_limits<scalar_type>::epsilon();
}

BOOST_AUTO_TEST_SUITE(TestPoint3D)

BOOST_AUTO_TEST_CASE(testInstantiation)
{
  minimath::pointxyzd pd1;
  minimath::pointxyzd pd2(1,2,3);
}

BOOST_AUTO_TEST_CASE(testEquality)
{
  BOOST_CHECK(minimath::pointxyzd()==minimath::pointxyzd());
  minimath::pointxyzd pd1(1, 2, 3);
  minimath::pointxyzd pd2(1,2,3);
  BOOST_CHECK( pd1 == pd2);
}

BOOST_AUTO_TEST_CASE(testInequality)
{
  minimath::pointxyzd pd1(10, 20, 30);
  minimath::pointxyzd pd2(1,2,3);
  BOOST_CHECK( pd1 != pd2);
}

BOOST_AUTO_TEST_CASE(testCloseInequality)
{
  minimath::pointxyzd pd1(10, 20, 30);
  minimath::pointxyzd pd2(10.00001,20,30);
  BOOST_CHECK( pd1 != pd2);
}

BOOST_AUTO_TEST_CASE(testAccessX)
{
  minimath::pointxyzd pd1(10, 20, 30);
  BOOST_CHECK( minimath::compare_with_tolerance(pd1.x(), 10., EPS));
}

BOOST_AUTO_TEST_CASE(testAccessY)
{
  minimath::pointxyzd pd1(10, 20, 30);
  BOOST_CHECK( minimath::compare_with_tolerance(pd1.y(), 20., EPS) );
}

BOOST_AUTO_TEST_CASE(testAccessZ)
{
  minimath::pointxyzd pd1(10, 20, 30);
  BOOST_CHECK( minimath::compare_with_tolerance(pd1.z(), 30., EPS) );
}

BOOST_AUTO_TEST_CASE(testSetX)
{
  minimath::pointxyzd pd1;
  pd1.x(3.14);
  BOOST_CHECK( minimath::compare_with_tolerance(pd1.x(), 3.14, EPS) );
}

BOOST_AUTO_TEST_CASE(testSetY)
{
  minimath::pointxyzd pd1;
  pd1.y(3.14);
  BOOST_CHECK(  minimath::compare_with_tolerance(pd1.y(), 3.14, EPS) );
}

BOOST_AUTO_TEST_CASE(testSetZ)
{
  minimath::pointxyzd pd1;
  pd1.z(3.14);
  BOOST_CHECK(  minimath::compare_with_tolerance(pd1.z(), 3.14, EPS) );
}

BOOST_AUTO_TEST_CASE(testCopyConstruction)
{
  minimath::pointxyzd pd1(1,2,3);
  minimath::pointxyzd pd2 = pd1;
  BOOST_CHECK( pd1 == pd2);
}

BOOST_AUTO_TEST_CASE(testAssignment)
{
  minimath::pointxyzd pd1(1,2,3);
  minimath::pointxyzd pd2;
  pd2 = pd1;
  BOOST_CHECK( pd1 == pd2);
}

BOOST_AUTO_TEST_CASE(testPlusEquals)
{
  minimath::pointxyzd pd(1, 2, 3);
  pd += minimath::pointxyzd(10,20,30);
  BOOST_CHECK( pd == minimath::pointxyzd(11,22,33));
}

BOOST_AUTO_TEST_CASE(testMinusEquals)
{
  minimath::pointxyzd pd(11, 22, 33);
  pd -= minimath::pointxyzd(10,20,30);
  BOOST_CHECK( pd == minimath::pointxyzd(1,2,3));
}

BOOST_AUTO_TEST_CASE(testTimesEqualsScalar)
{
  minimath::pointxyzd pd(1, 2, 3);
  pd *= 11;
  BOOST_CHECK( pd == minimath::pointxyzd(11,22,33));

}

BOOST_AUTO_TEST_CASE(testDivideEqualsScalar)
{
  minimath::pointxyzd pd(100, 200, 300);
  pd /= 10;
  BOOST_CHECK( pd == minimath::pointxyzd(10,20,30));
}

BOOST_AUTO_TEST_CASE(testTimesScalar)
{
  minimath::pointxyzd pd = minimath::pointxyzd(1, 2, 3) * 11;
  BOOST_CHECK( pd == minimath::pointxyzd(11,22,33));

}

BOOST_AUTO_TEST_CASE(testDivideScalar)
{
  minimath::pointxyzd pd = minimath::pointxyzd(100, 200, 300)/10;
  BOOST_CHECK( pd == minimath::pointxyzd(10,20,30));
}


BOOST_AUTO_TEST_CASE(testMagnitudeSquared)
{
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::mag2(minimath::pointxyzd(1,1,1)), 3., EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::mag2(minimath::pointxyzd(5,5,5)), 75., EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::mag2(minimath::pointxyzd(5,0,0)), 25., EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::mag2(minimath::pointxyzd(0,5,0)), 25., EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::mag2(minimath::pointxyzd(0,0,5)), 25., EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::mag2(minimath::pointxyzd(-5,0,5)), 50., EPS));
}

BOOST_AUTO_TEST_CASE(testDistanceSquared)
{
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,1,1),
                                                        minimath::pointxyzd(1,1,1)), 0., EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,1,1),
                                                        minimath::pointxyzd(0,0,0)), 3., EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,1,0),
                                                        minimath::pointxyzd(0,0,0)), 2., EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,0,1),
                                                        minimath::pointxyzd(0,0,0)), 2., EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,0,0),
                                                        minimath::pointxyzd(0,0,0)), 1., EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(0,1,0),
                                                        minimath::pointxyzd(0,0,0)), 1., EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(0,0,1),
                                                        minimath::pointxyzd(0,0,0)), 1., EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,0,0),
                                                        minimath::pointxyzd(-1,0,0)), 4., EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(minimath::dist2(minimath::pointxyzd(1,1,1),
                                                        minimath::pointxyzd(-1,-1,-1)), 12., EPS));
}

BOOST_AUTO_TEST_CASE(testDotProduct)
{
  BOOST_CHECK(minimath::compare_with_tolerance(3., minimath::dot(minimath::pointxyzd(1,1,1),
                                                          minimath::pointxyzd(1,1,1)), EPS));
  // parallel opposite direction
  BOOST_CHECK(minimath::compare_with_tolerance(-3., minimath::dot(minimath::pointxyzd(1,1,1),
                                                           minimath::pointxyzd(-1,-1,-1)), EPS));
  // orthoginal
  BOOST_CHECK(minimath::compare_with_tolerance(0., minimath::dot(minimath::pointxyzd(1,0,0),
                                                          minimath::pointxyzd(0,1,0)), EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(0., minimath::dot(minimath::pointxyzd(1,0,0),
                                                          minimath::pointxyzd(0,0,1)), EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(0., minimath::dot(minimath::pointxyzd(0,1,0),
                                                          minimath::pointxyzd(1,0,0)), EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(0., minimath::dot(minimath::pointxyzd(0,1,0),
                                                          minimath::pointxyzd(0,0,1)), EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(0., minimath::dot(minimath::pointxyzd(0,0,1),
                                                          minimath::pointxyzd(1,0,0)), EPS));
  BOOST_CHECK(minimath::compare_with_tolerance(0., minimath::dot(minimath::pointxyzd(0,0,1),
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
    BOOST_CHECK(compare_with_tolerance(d, pointxyzd::value_type(1.), 5.0e-16));
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
    BOOST_CHECK(compare_with_tolerance(p.normalize(), d, EPS));
    std::stringstream ss;
    ss << "mag2(p) -1 = " << mag2(p) - pointxyzd::value_type(1.);
    ss << " EPS " << EPS;
    d = mag2(p);
    BOOST_CHECK_MESSAGE(ss.str().c_str(), compare_with_tolerance(d, pointxyzd::value_type(1.), 5.0e-16));
  }
}
}

BOOST_AUTO_TEST_CASE(testNormalize)
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

BOOST_AUTO_TEST_CASE(testNormalizeNonMember)
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

BOOST_AUTO_TEST_SUITE_END()
