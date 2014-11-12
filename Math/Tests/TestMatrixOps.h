//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_MATRIXOPS_H_
#define TESTS_MATRIXOPS_H_


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestMatrixOps : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestMatrixOps);
  CPPUNIT_TEST(testXRotations);
  CPPUNIT_TEST(testYRotations);
  CPPUNIT_TEST(testZRotations);
  CPPUNIT_TEST_SUITE_END();

 public:

  void setUp();

 protected:

  void testXRotations();
  void testYRotations();
  void testZRotations();

 private:

  typedef Math::Matrix<double,3,1> Point;

  Point p100;
  Point p010;
  Point p001;
  Point p110;
  Point p011;
  Point p101;
  Point p111;
  Point pm100;
  Point p0m10;
  Point p00m1;
  Point pmm1m10;
  Point p0m1m1;
  Point pm10m1;
  Point pm1m1m1;

};

#endif
