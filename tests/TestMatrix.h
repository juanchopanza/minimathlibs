//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_MATRIX_H_
#define TESTS_MATRIX_H_


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestMatrix : public CppUnit::TestFixture
{
  
  CPPUNIT_TEST_SUITE(TestMatrix);
  CPPUNIT_TEST(testDefaultConstruction);
  CPPUNIT_TEST(testZeroMatrixConstruction);
  CPPUNIT_TEST(testIdentityMatrixConstruction);
  CPPUNIT_TEST(testScalarConstruction);
  CPPUNIT_TEST(testCopyConstruction);
  CPPUNIT_TEST(testAssignment);
  CPPUNIT_TEST(testZeroMatrixAssignment);
  CPPUNIT_TEST(testIdentityMatrixAssignment);
  CPPUNIT_TEST(testEquality);
  CPPUNIT_TEST(testInequality);
  CPPUNIT_TEST(testPlusEquals);
  CPPUNIT_TEST(testMinusEquals);
  CPPUNIT_TEST(testPlusEqualsScalar);
  CPPUNIT_TEST(testMinusEqualsScalar);
  CPPUNIT_TEST(testTimesEqualsScalar);
  CPPUNIT_TEST(testDivideEqualsScalar);
  CPPUNIT_TEST(testMatrixPlusScalar);
  CPPUNIT_TEST(testMatrixMinusScalar);
  CPPUNIT_TEST(testScalarPlusMatrix);
  CPPUNIT_TEST(testScalarMinusMatrix);
  CPPUNIT_TEST(testMatrixTimesScalar);
  CPPUNIT_TEST(testTranspose);
  CPPUNIT_TEST(testInverse);
  CPPUNIT_TEST(testInvert);
  CPPUNIT_TEST(testLeftInverse);

  CPPUNIT_TEST_SUITE_END();

  void testDefaultConstruction();
  void testZeroMatrixConstruction();
  void testZeroMatrixAssignment();
  void testIdentityMatrixConstruction();
  void testIdentityMatrixAssignment();
  void testScalarConstruction();
  void testCopyConstruction();
  void testAssignment();
  void testEquality();
  void testInequality();
  void testPlusEquals();
  void testMinusEquals();
  void testPlusEqualsScalar();
  void testMinusEqualsScalar();
  void testTimesEqualsScalar();
  void testDivideEqualsScalar();
  void testMatrixPlusScalar();
  void testMatrixMinusScalar();
  void testScalarPlusMatrix();
  void testScalarMinusMatrix();
  void testMatrixTimesScalar();
  void testTranspose();
  void testLeftInverse();
  void testInverse();
  void testInvert();

};

#endif
