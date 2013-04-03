//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_POINT3D_H__
#define TESTS_POINT3D_H__

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Point3D.h"
#include "Math/Point3DOps.h"
#include "Math/Utils.h" // for FP comparisons
#include <iostream>
#include <limits>
#include <cmath>

class TestPoint3D : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestPoint3D);
  CPPUNIT_TEST(testInstantiation);
  CPPUNIT_TEST(testCopyConstruction);
  CPPUNIT_TEST(testAssignment);
  CPPUNIT_TEST(testEquality);
  CPPUNIT_TEST(testInequality);
  CPPUNIT_TEST(testCloseInequality);
  CPPUNIT_TEST(testAccessX);
  CPPUNIT_TEST(testAccessY);
  CPPUNIT_TEST(testAccessZ);
  CPPUNIT_TEST(testSetX);
  CPPUNIT_TEST(testSetY);
  CPPUNIT_TEST(testSetZ);
  CPPUNIT_TEST(testPlusEquals);
  CPPUNIT_TEST(testMinusEquals);
  CPPUNIT_TEST(testTimesEqualsScalar);
  CPPUNIT_TEST(testDivideEqualsScalar);
  CPPUNIT_TEST(testTimesScalar);
  CPPUNIT_TEST(testDivideScalar);
  CPPUNIT_TEST(testMagnitudeSquared);
  CPPUNIT_TEST(testDistanceSquared);
  CPPUNIT_TEST(testDotProduct);
  CPPUNIT_TEST_SUITE_END();

  Math::PointXYZD::value_type EPS; 

 public:

  void Setup()
  {
    EPS = std::numeric_limits<Math::PointXYZD::value_type>::epsilon();
  }

 protected:

  void testInstantiation()
  {
    Math::PointXYZD pd1;
    Math::PointXYZD pd2(1,2,3);
  }

  void testEquality()
  {
    CPPUNIT_ASSERT(Math::PointXYZD()==Math::PointXYZD());
    Math::PointXYZD pd1(1, 2, 3);
    Math::PointXYZD pd2(1,2,3);
    CPPUNIT_ASSERT( pd1 == pd2);
  }

  void testInequality()
  {
    Math::PointXYZD pd1(10, 20, 30);
    Math::PointXYZD pd2(1,2,3);
    CPPUNIT_ASSERT( pd1 != pd2);
  }

  void testCloseInequality()
  {
    Math::PointXYZD pd1(10, 20, 30);
    Math::PointXYZD pd2(10.00001,20,30);
    CPPUNIT_ASSERT( pd1 != pd2);
  }

  void testAccessX()
  {
    Math::PointXYZD pd1(10, 20, 30);
    CPPUNIT_ASSERT( Math::compareWithTolerance(pd1.x(), 10., EPS));
  }
 
  void testAccessY()
  {
    Math::PointXYZD pd1(10, 20, 30);
    CPPUNIT_ASSERT( Math::compareWithTolerance(pd1.y(), 20., EPS) );
  }

 void testAccessZ()
  {
    Math::PointXYZD pd1(10, 20, 30);
    CPPUNIT_ASSERT( Math::compareWithTolerance(pd1.z(), 30., EPS) );
  }

  void testSetX()
  {
    Math::PointXYZD pd1;
    pd1.x(3.14);
    CPPUNIT_ASSERT( Math::compareWithTolerance(pd1.x(), 3.14, EPS) );
  }
  
  void testSetY()
  {
    Math::PointXYZD pd1;
    pd1.y(3.14);
    CPPUNIT_ASSERT(  Math::compareWithTolerance(pd1.y(), 3.14, EPS) );
  }

  void testSetZ()
  {
    Math::PointXYZD pd1;
    pd1.z(3.14);
    CPPUNIT_ASSERT(  Math::compareWithTolerance(pd1.z(), 3.14, EPS) );
  }
 
  void testCopyConstruction() 
  {
    Math::PointXYZD pd1(1,2,3);
    Math::PointXYZD pd2 = pd1;
    CPPUNIT_ASSERT( pd1 == pd2);
  }
  
  void testAssignment()  {
    Math::PointXYZD pd1(1,2,3);
    Math::PointXYZD pd2;
    pd2 = pd1;
    CPPUNIT_ASSERT( pd1 == pd2);
  }

  void testPlusEquals()
  {
    Math::PointXYZD pd(1, 2, 3);
    pd += Math::PointXYZD(10,20,30);
    CPPUNIT_ASSERT( pd == Math::PointXYZD(11,22,33));
  }

  void testMinusEquals()
  {
    Math::PointXYZD pd(11, 22, 33);
    pd -= Math::PointXYZD(10,20,30);
    CPPUNIT_ASSERT( pd == Math::PointXYZD(1,2,3));
  }

  void testTimesEqualsScalar()
  {
    Math::PointXYZD pd(1, 2, 3);
    pd *= 11;
    CPPUNIT_ASSERT( pd == Math::PointXYZD(11,22,33));

  }

  void testDivideEqualsScalar()
  {
    Math::PointXYZD pd(100, 200, 300);
    pd /= 10;
    CPPUNIT_ASSERT( pd == Math::PointXYZD(10,20,30));
  }

  void testTimesScalar()
  {
    Math::PointXYZD pd = Math::PointXYZD(1, 2, 3) * 11;
    CPPUNIT_ASSERT( pd == Math::PointXYZD(11,22,33));

  }

  void testDivideScalar()
  {
    Math::PointXYZD pd = Math::PointXYZD(100, 200, 300)/10;
    CPPUNIT_ASSERT( pd == Math::PointXYZD(10,20,30));
  }


  void testMagnitudeSquared()
  {
    CPPUNIT_ASSERT(Math::mag2(Math::PointXYZD(1,1,1)) == 3.);
    CPPUNIT_ASSERT(Math::mag2(Math::PointXYZD(5,5,5)) == 75.);
    CPPUNIT_ASSERT(Math::mag2(Math::PointXYZD(5,0,0)) == 25.);
    CPPUNIT_ASSERT(Math::mag2(Math::PointXYZD(0,5,0)) == 25.);
    CPPUNIT_ASSERT(Math::mag2(Math::PointXYZD(0,0,5)) == 25.);
    CPPUNIT_ASSERT(Math::mag2(Math::PointXYZD(-5,0,5)) == 50.);
  }

  void testDistanceSquared()
  {
    CPPUNIT_ASSERT(Math::dist2(Math::PointXYZD(1,1,1),
                               Math::PointXYZD(1,1,1)) == 0.);
    CPPUNIT_ASSERT(Math::dist2(Math::PointXYZD(1,1,1),
                               Math::PointXYZD(0,0,0)) == 3.);
    CPPUNIT_ASSERT(Math::dist2(Math::PointXYZD(1,1,0),
                               Math::PointXYZD(0,0,0)) == 2.);
    CPPUNIT_ASSERT(Math::dist2(Math::PointXYZD(1,0,1),
                               Math::PointXYZD(0,0,0)) == 2.);
    CPPUNIT_ASSERT(Math::dist2(Math::PointXYZD(1,0,0),
                               Math::PointXYZD(0,0,0)) == 1.);
    CPPUNIT_ASSERT(Math::dist2(Math::PointXYZD(0,1,0),
                               Math::PointXYZD(0,0,0)) == 1.);
    CPPUNIT_ASSERT(Math::dist2(Math::PointXYZD(0,0,1),
                               Math::PointXYZD(0,0,0)) == 1.);
    CPPUNIT_ASSERT(Math::dist2(Math::PointXYZD(1,0,0),
                               Math::PointXYZD(-1,0,0)) == 4.);
    CPPUNIT_ASSERT(Math::dist2(Math::PointXYZD(1,1,1),
                               Math::PointXYZD(-1,-1,-1)) == 12.);
  }

  void testDotProduct()
  {
    CPPUNIT_ASSERT(3 == Math::dot(Math::PointXYZD(1,1,1),
                                  Math::PointXYZD(1,1,1)));
    // parallel opposite direction
    CPPUNIT_ASSERT(-3 == Math::dot(Math::PointXYZD(1,1,1),
                                   Math::PointXYZD(-1,-1,-1)));
    // orthoginal
    CPPUNIT_ASSERT( 0 == Math::dot(Math::PointXYZD(1,0,0),
                                   Math::PointXYZD(0,1,0)));
    CPPUNIT_ASSERT( 0 == Math::dot(Math::PointXYZD(1,0,0),
                                   Math::PointXYZD(0,0,1))); 
    CPPUNIT_ASSERT( 0 == Math::dot(Math::PointXYZD(0,1,0),
                                   Math::PointXYZD(1,0,0))); 
    CPPUNIT_ASSERT( 0 == Math::dot(Math::PointXYZD(0,1,0),
                                   Math::PointXYZD(0,0,1))); 
    CPPUNIT_ASSERT( 0 == Math::dot(Math::PointXYZD(0,0,1),
                                   Math::PointXYZD(1,0,0))); 
    CPPUNIT_ASSERT( 0 == Math::dot(Math::PointXYZD(0,0,1),
                                   Math::PointXYZD(0,1,0))); 
  }

};


#endif
