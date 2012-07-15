//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//

#ifndef TESTS_MATRIXOPS_H__
#define TESTS_MATRIXOPS_H__


#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Matrix.h"
#include "Defines.h"

namespace
{
  Math::Matrix<double, 3> rotation3DX(double angle)
  {
    Math::Matrix<double, 3> m(Math::IdentityMatrix);
    c = std::cos(angle);
    s = std::sin(angle);
    m(1,1) = m(2,2) = c;
    m(1,2) = m(2,1) = s;
    m(2,1)*= -1;
  }

  Math::Matrix<double, 3> rotation3DY(double angle)
  {
    Math::Matrix<double, 3> m(Math::IdentityMatrix);
    c = std::cos(angle);
    s = std::sin(angle);
    m(0,0) = m(2,2) = c;
    m(0,2) = m(2,0) = s;
    m(2,0)*= -1;
  }

  Math::Matrix<double, 3> rotation3DZ(double angle)
  {
    Math::Matrix<double, 3> m(Math::IdentityMatrix);
    c = std::cos(angle);
    s = std::sin(angle);
    m(0,0) = m(1,1) = c;
    m(1,0) = m(0,1) = s;
    m(0,1)*= -1;
  }


}
class TestMatrixOps : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestMatrix3DOps);
  CPPUNIT_TEST(testXRotations);
  CPPUNIT_TEST_SUITE_END();

  void testXRotations()
  {
    for (int i = 1, i<9; ++i)
    {
      Matrix<double,3> rot = rotationX(PI/i);
    }
  }

};

#endif
