//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_TRANSLATION3D_H_
#define TESTS_TRANSLATION3D_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestTranslation3D : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestTranslation3D);
  CPPUNIT_TEST(testInstantiation);
  CPPUNIT_TEST(testDefaultEquality);
  CPPUNIT_TEST(testCopyConstruction);
  CPPUNIT_TEST(testAssignment);
  CPPUNIT_TEST(testNullTranslation);
  CPPUNIT_TEST(testTranslatePoint);
  CPPUNIT_TEST(testCompoundTranslation);
  CPPUNIT_TEST(testInverse);
  CPPUNIT_TEST(testInvert);
  CPPUNIT_TEST_SUITE_END();

 protected:

  void testInstantiation();
  void testDefaultEquality();
  void testCopyConstruction();
  void testAssignment();
  void testNullTranslation();
  void testTranslatePoint();
  void testCompoundTranslation();
  void testInverse();
  void testInvert();

};


#endif

