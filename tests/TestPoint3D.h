//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_POINT3D_H_
#define TESTS_POINT3D_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Point3D.h"
#include "Math/Point3DOps.h"
#include "Math/Utils.h" // for FP comparisons

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
  CPPUNIT_TEST(testNormalize);
  CPPUNIT_TEST(testNormalizeNonMember);
  CPPUNIT_TEST_SUITE_END();

  Math::PointXYZD::value_type EPS; 

 public:

  void Setup();
 protected:

  void testInstantiation();
  void testEquality();
  void testInequality();
  void testCloseInequality();
  void testAccessX();
  void testAccessY();
  void testAccessZ();
  void testSetX();
  void testSetY();
  void testSetZ();
  void testCopyConstruction();
  void testAssignment();
  void testPlusEquals();
  void testMinusEquals();
  void testTimesEqualsScalar();
  void testDivideEqualsScalar();
  void testTimesScalar();
  void testDivideScalar();
  void testMagnitudeSquared();
  void testDistanceSquared();
  void testDotProduct();
  void testNormalize();
  void testNormalizeNonMember();

};


#endif
