//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Matrix.h"
#include "Math/MatrixOps.h"
#include "Defines.h"
#include "TestMatrixOps.h"

typedef Math::Matrix<double,3,1> Point;

namespace
{

Math::Matrix<double, 3> rotation3DX(double angle)
{
  Math::Matrix<double, 3> m = Math::IdentityMatrix();
  const double c = std::cos(angle);
  const double s = std::sin(angle);
  m(1,1) = m(2,2) = c;
  m(1,2) = m(2,1) = s;
  m(2,1)*= -1;
  return m;
}

Math::Matrix<double, 3> rotation3DY(double angle)
{
  Math::Matrix<double, 3> m = Math::IdentityMatrix();
  const double c = std::cos(angle);
  const double s = std::sin(angle);
  m(0,0) = m(2,2) = c;
  m(0,2) = m(2,0) = s;
  m(2,0)*= -1;
  return m;
}

Math::Matrix<double, 3> rotation3DZ(double angle)
{
  Math::Matrix<double, 3> m = Math::IdentityMatrix();
  const double c = std::cos(angle);
  const double s = std::sin(angle);
  m(0,0) = m(1,1) = c;
  m(1,0) = m(0,1) = s;
  m(0,1)*= -1;
  return m;
}

}

void TestMatrixOps::setUp()
{
  std::cout << std::boolalpha;
  p100_(0,0) = 1;
  p010_(1,0) = 1;
  p001_(2,0) = 1;
  p110_(0,0) = 1;
  p110_(1,0) = 1;
  p011_(1,0) = 1;
  p011_(2,0) = 1;
  p101_(0,0) = 1;
  p101_(2,0) = 1;
  p111_ += 1;

}

void TestMatrixOps::testXRotations()
{
  for (int i = 1; i<9; ++i)
  {
    Math::Matrix<double,3> rot = rotation3DX(PI/i);
    Math::Matrix<double,3> orig;
    Math::setColumn(orig, p100_, 0);
    Math::setColumn(orig, p010_, 1);
    Math::setColumn(orig, p111_, 2);

    Math::Matrix<double,3> prime = rot*orig;
    bool success = true;
    Math::Matrix<double,3> rot2 = Math::transformation(orig, prime, success);
    if (success)
    {
      CPPUNIT_ASSERT(Math::equal(rot, rot2, 1));
    } else {
      std::cout << "\nInversion failed for angle: PI/" << i;
      std::cout <<"\nOriginal matrix:\n " << orig << "\n";
    }
  }
}

void TestMatrixOps::testYRotations()
{
  for (int i = 1; i<9; ++i)
  {
    Math::Matrix<double,3> rot = rotation3DY(PI/i);
    Math::Matrix<double,3> orig;
    Math::setColumn(orig, p100_, 0);
    Math::setColumn(orig, p010_, 1);
    Math::setColumn(orig, p111_, 2);

    Math::Matrix<double,3> prime = rot*orig;
    bool success = true;
    Math::Matrix<double,3> rot2 = Math::transformation(orig, prime, success);
    if (success)
    {
      CPPUNIT_ASSERT(Math::equal(rot, rot2, 1));
    } else {
      std::cout << "\nInversion failed for angle: PI/" << i;
      std::cout <<"\nOriginal matrix:\n " << orig << "\n";
    }
  }
}

void TestMatrixOps::testZRotations()
{
  for (int i = 1; i<9; ++i)
  {
    Math::Matrix<double,3> rot = rotation3DZ(PI/i);
    Math::Matrix<double,3> orig;
    Math::setColumn(orig, p100_, 0);
    Math::setColumn(orig, p010_, 1);
    Math::setColumn(orig, p111_, 2);

    Math::Matrix<double,3> prime = rot*orig;
    bool success = true;
    Math::Matrix<double,3> rot2 = Math::transformation(orig, prime, success);
    if (success)
    {
      CPPUNIT_ASSERT(Math::equal(rot, rot2, 1));
    } else {
      std::cout << "\nInversion failed for angle: PI/" << i;
      std::cout <<"\nOriginal matrix:\n " << orig << "\n";
    }
  }
}

