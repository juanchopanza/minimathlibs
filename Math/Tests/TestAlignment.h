//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_TESTALIGNMENT_H_
#define TESTS_TESTALIGNMENT_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestAlignment : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestAlignment);
  CPPUNIT_TEST(testRotation);
  CPPUNIT_TEST(testTranslation);
  CPPUNIT_TEST(testRotation3DXAndTranslation);
  CPPUNIT_TEST(testRotation3DYAndTranslation);
  CPPUNIT_TEST(testRotation3DZAndTranslation);
  CPPUNIT_TEST(testTranslationAndRotation3DX);
  CPPUNIT_TEST(testTranslationAndRotation3DY);
  CPPUNIT_TEST(testTranslationAndRotation3DZ);
  CPPUNIT_TEST_SUITE_END();

  void testTranslation();
  void testRotation();
  void testRotation3DXAndTranslation();
  void testRotation3DYAndTranslation();
  void testRotation3DZAndTranslation();
  void testTranslationAndRotation3DX();
  void testTranslationAndRotation3DY();
  void testTranslationAndRotation3DZ();

};

#endif // TESTS_TESTALIGNMENT_H_
