//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_TESTROTATION3DZYX_H_
#define TESTS_TESTROTATION3DZYX_H_


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestRotation3DZYX : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestRotation3DZYX);
  CPPUNIT_TEST(testInstantiation);
  CPPUNIT_TEST(testDefaultEquality);
  CPPUNIT_TEST(testCopyConstruction);
  CPPUNIT_TEST(testAssignment);
  CPPUNIT_TEST(testNullRotation);
  CPPUNIT_TEST(testRotatePoint45X);
  CPPUNIT_TEST(testRotatePoint90X);
  CPPUNIT_TEST(testRotatePoint180X);
  CPPUNIT_TEST(testRotatePoint45Y);
  CPPUNIT_TEST(testRotatePoint90Y);
  CPPUNIT_TEST(testRotatePoint180Y);
  CPPUNIT_TEST(testRotatePoint45Z);
  CPPUNIT_TEST(testRotatePoint90Z);
  CPPUNIT_TEST(testRotatePoint180Z);
  CPPUNIT_TEST(testAssignRotation3DX);
  CPPUNIT_TEST(testAssignRotation3DY);
  CPPUNIT_TEST(testAssignRotation3DZ);
  CPPUNIT_TEST(testZYXRotations);
  CPPUNIT_TEST(testInverse);
  CPPUNIT_TEST(testInvert);
  CPPUNIT_TEST_SUITE_END();

 protected:

  void testInstantiation();
  void testDefaultEquality();
  void testCopyConstruction();
  void testAssignment();
  void testNullRotation();
  void testRotatePoint45X();
  void testRotatePoint90X();
  void testRotatePoint180X();
  void testRotatePoint45Y();
  void testRotatePoint90Y();
  void testRotatePoint180Y();
  void testRotatePoint45Z();
  void testRotatePoint90Z();
  void testRotatePoint180Z();
  void testAssignRotation3DX();
  void testAssignRotation3DY();
  void testAssignRotation3DZ();
  void testZYXRotations();
  void testInverse();
  void testInvert();

};

#endif

