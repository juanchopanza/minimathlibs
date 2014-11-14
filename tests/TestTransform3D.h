//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_TRANSFORM3D_H_
#define TESTS_TRANSFORM3D_H_


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Point3D.h"


class TestTransform3D : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestTransform3D);
  CPPUNIT_TEST(testInstantiation);
  CPPUNIT_TEST(testDefaultEquality);
  CPPUNIT_TEST(testDefaultIsIdentity);
  CPPUNIT_TEST(testCopyConstruction);
  CPPUNIT_TEST(testAssignment);
  CPPUNIT_TEST(testTranslation);
  CPPUNIT_TEST(testRotation3D);
  CPPUNIT_TEST(testRotationX45);
  CPPUNIT_TEST(testRotationX90);
  CPPUNIT_TEST(testRotationX180);
  CPPUNIT_TEST(testRotationY45);
  CPPUNIT_TEST(testRotationY90);
  CPPUNIT_TEST(testRotationY180);
  CPPUNIT_TEST(testRotationZ45);
  CPPUNIT_TEST(testRotationZ90);
  CPPUNIT_TEST(testRotationZ180);
  CPPUNIT_TEST(testNullRotationAndTranslation);
  CPPUNIT_TEST(testRotationXAndTranslation);
  CPPUNIT_TEST(testRotationYAndTranslation);
  CPPUNIT_TEST(testRotationZAndTranslation);

  CPPUNIT_TEST(testTranslationAndNullRotation);
  CPPUNIT_TEST(testTranslationAndRotationX);
  CPPUNIT_TEST(testTranslationAndRotationY);
  CPPUNIT_TEST(testTranslationAndRotationZ);

  CPPUNIT_TEST(testMultiplication);
  CPPUNIT_TEST(testInverse);
  CPPUNIT_TEST(testInvert);

  CPPUNIT_TEST_SUITE_END();

 public:
  
  void setUp();

 protected:

  void testInstantiation();
  void testDefaultEquality();
  void testDefaultIsIdentity();
  void testCopyConstruction();
  void testAssignment();
  void testTranslation();
  void testRotation3D();
  void testRotationX45();
  void testRotationX90();
  void testRotationX180();
  void testRotationY45();
  void testRotationY90();
  void testRotationY180();
  void testRotationZ45();
  void testRotationZ90();
  void testRotationZ180();
  void testNullRotationAndTranslation();
  void testRotationXAndTranslation();
  void testRotationYAndTranslation();
  void testRotationZAndTranslation();
  void testTranslationAndNullRotation();
  void testTranslationAndRotationX();
  void testTranslationAndRotationY();
  void testTranslationAndRotationZ();
  void testMultiplication();
  void testInverse();
  void testInvert();

};



#endif

