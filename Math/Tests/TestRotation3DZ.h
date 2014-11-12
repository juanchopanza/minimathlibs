//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_TESTROTATION3DZ_H_
#define TESTS_TESTROTATION3DZ_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestRotation3DZ : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestRotation3DZ);
  CPPUNIT_TEST(testInstantiation);
  CPPUNIT_TEST(testDefaultEquality);
  CPPUNIT_TEST(testCopyConstruction);
  CPPUNIT_TEST(testAssignment);
  CPPUNIT_TEST(testRotatePoint0);
  CPPUNIT_TEST(testRotatePoint45);
  CPPUNIT_TEST(testRotatePoint90);
  CPPUNIT_TEST(testRotatePoint180);
  CPPUNIT_TEST(testInverse);
  CPPUNIT_TEST(testInvert);
  CPPUNIT_TEST_SUITE_END();

 protected:

  void testInstantiation();
  void testDefaultEquality();
  void testCopyConstruction();
  void testAssignment();
  void testRotatePoint0();
  void testRotatePoint45();
  void testRotatePoint90();
  void testRotatePoint180();
  void testInverse();
  void testInvert();

};

#endif

