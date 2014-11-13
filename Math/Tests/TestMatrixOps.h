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
#include "Math/Matrix.h"

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

  Point p100_;
  Point p010_;
  Point p001_;
  Point p110_;
  Point p011_;
  Point p101_;
  Point p111_;
  Point pm100_;
  Point p0m10_;
  Point p00m1_;
  Point pmm1m10_;
  Point p0m1m1_;
  Point pm10m1_;
  Point pm1m1m1_;

};

#endif
