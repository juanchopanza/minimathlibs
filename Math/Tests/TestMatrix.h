//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_MATRIX_H_
#define TESTS_MATRIX_H_


#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Matrix.h"
#include "Math/Utils.h"

namespace 
{
// test if all elements of a matrix have a particular value
template <typename M>
bool valueEquality(const M& m, 
                   typename M::value_type v, 
                   typename M::value_type tol = std::numeric_limits<typename M::value_type>::epsilon()) {

  for (unsigned int r = 0; r < m.rows(); ++r)
  {
    for (unsigned int c = 0; c < m.cols(); ++c)
    {
      if ( std::abs(m(r,c) - v) > tol) {
        std::cout << "\nm(" << r << ", " << c << ") = " << m(r,c) << "\n";
        std::cout << "\n" << m << "\n";
        return false;
      }
    }
  }
  return true;
}

// test if two elements are within epsilon of each other
template <typename T>
bool valueEquality(const T& lhs, const T& rhs)
{
  return std::abs(rhs-lhs) < std::numeric_limits<T>::epsilon();
}

// test if a matrix is an identity matrix
template <typename M>
bool isIdentity(const M& m, 
                typename M::value_type tol = std::numeric_limits<typename M::value_type>::epsilon()) {

  if (m.rows() != m.cols()) return false;
  for (unsigned int r = 0; r < m.rows(); ++r)
  {
    for (unsigned int c = 0; c < m.cols(); ++c)
    {
      if (r==c)
      {
        if ( std::abs(m(r,c) - 1) > tol) return false;
      } else {
        if ( std::abs(m(r,c)) > tol) {
          std::cout << "\nm(" << r << ", " << c << ") = " << m(r,c) << "\n";
          std::cout << "\n" << m << "\n";
          return false;
        }
      }
    }
  }
  return true;
}

} // anonymous namespace

class TestMatrix : public CppUnit::TestFixture
{

  typedef Math::Matrix<double, 2> M2x2;
  typedef Math::Matrix<double, 3> M3x3;
  typedef Math::Matrix<double, 4> M4x4;
  typedef Math::Matrix<double, 5> M5x5;

  typedef Math::Matrix<double, 2,1> M2x1;
  typedef Math::Matrix<double, 3,2> M3x2;
  typedef Math::Matrix<double, 4,3> M4x3;
  typedef Math::Matrix<double, 5,4> M5x4;

  typedef Math::Matrix<double, 3,4> M3x4;
  typedef Math::Matrix<double, 4,5> M4x5;

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

  void testDefaultConstruction()
  {
    M2x2 a;
    M2x2 b;
    M2x2 c;
    CPPUNIT_ASSERT(valueEquality(a, 0.));
    CPPUNIT_ASSERT(valueEquality(b, 0.));
    CPPUNIT_ASSERT(valueEquality(c, 0.));
    CPPUNIT_ASSERT(2==a.rows());
    CPPUNIT_ASSERT(2==a.cols());
    CPPUNIT_ASSERT(4==a.size());
    CPPUNIT_ASSERT(a==b);
    CPPUNIT_ASSERT(a==c);
    CPPUNIT_ASSERT(b==c);

    M5x4 d, e, f;
    CPPUNIT_ASSERT(valueEquality(d, 0));
    CPPUNIT_ASSERT(valueEquality(e, 0));
    CPPUNIT_ASSERT(valueEquality(f, 0));
    CPPUNIT_ASSERT(5==e.rows());
    CPPUNIT_ASSERT(4==e.cols());
    CPPUNIT_ASSERT(20==e.size());
    CPPUNIT_ASSERT(d==e);
    CPPUNIT_ASSERT(d==f);
    CPPUNIT_ASSERT(e==f);

  }

  void testZeroMatrixConstruction()
  {
    M4x3 m = Math::ZeroMatrix();
    CPPUNIT_ASSERT(valueEquality(m, 0));
  }

  void testZeroMatrixAssignment()
  {
    M4x3 m;
    m = Math::ZeroMatrix();
    CPPUNIT_ASSERT(valueEquality(m, 0));
  }


  void testIdentityMatrixConstruction()
  {
    M4x4 m4 = Math::IdentityMatrix();
    CPPUNIT_ASSERT(isIdentity(m4));
    M5x5 m5 = Math::IdentityMatrix();
    CPPUNIT_ASSERT(isIdentity(m5));

  }

  void testIdentityMatrixAssignment()
  {
    M4x4 m;
    m = Math::IdentityMatrix();
    CPPUNIT_ASSERT(isIdentity(m));
  }


  void testScalarConstruction()
  {
    for (int  i = -20; i < 21; ++i) {
      M5x5 m(i);
      CPPUNIT_ASSERT(valueEquality(m, i));
    }
  }

  void testCopyConstruction()
  {
    M4x3 m;
    for (unsigned int i = 0; i< m.size(); ++i) {
      m[i] = i;
    }
    M4x3 m2(m);
    CPPUNIT_ASSERT(m2==m);
  }

  void testAssignment()
  {
    M4x3 m;
    for (unsigned int i = 0; i< m.size(); ++i) {
      m[i] = i;
    }
    M4x3 m2;
    m2 = m;
    CPPUNIT_ASSERT(m2==m);

  }

  void testEquality()
  {
    M4x3 m1, m2;
    for (unsigned int i = 0; i< m1.size(); ++i) {
      m1[i] = i;
      m2[i] = i;
    }
    CPPUNIT_ASSERT(m2==m1);

  }

  void testInequality()
  {
    M4x3 m;
    for (unsigned int i = 0; i< m.size(); ++i) {
      m[i] = i;
    }
    M4x3 m2;
    CPPUNIT_ASSERT(m2!=m);
  }


  void testPlusEqualsScalar()
  {
    M4x3 m;
    for (unsigned int i = 0; i< m.size(); ++i) {
      m[i] = i;
    }
    m += 100;
    for (unsigned int i = 0; i< m.size(); ++i) {
      CPPUNIT_ASSERT(valueEquality(m[i], M4x3::value_type(i) + 100));
    }
  }

  void testMinusEqualsScalar()
  {
    M4x3 m;
    for (unsigned int i = 0; i< m.size(); ++i) {
      m[i] = i;
    }
    m -= 100;
    for (unsigned int i = 0; i< m.size(); ++i) {
      CPPUNIT_ASSERT(valueEquality(m[i], M4x3::value_type(i) - 100.));
    }
  }
   
  void testPlusEquals()
  {
    M3x3 m1;
    for (unsigned int i = 0; i< m1.size(); ++i) {
      m1[i] = i;
    }
    M3x3 m2(10);
    m1 += m2;
    for (unsigned int i = 0; i< m1.size(); ++i) {
      CPPUNIT_ASSERT(valueEquality(m1[i], M3x3::value_type(i) + 10));
    }

  }

  void testMinusEquals()
  {
    M3x3 m1;
    for (unsigned int i = 0; i< m1.size(); ++i) {
      m1[i] = 10*i;
    }
    M3x3 m2(10);
    m1 -= m2;
    for (unsigned int i = 0; i< m1.size(); ++i) {
      CPPUNIT_ASSERT(valueEquality(m1[i], M3x3::value_type(10)*(int(i) -1) ));
    }
  }

  void testTimesEqualsScalar()
  {
    M4x3 m;
    for (unsigned int i = 0; i< m.size(); ++i) {
      m[i] = i;
    }
    m *= 100;
    for (unsigned int i = 0; i< m.size(); ++i) {
      CPPUNIT_ASSERT(valueEquality(m[i], M4x3::value_type(i) * 100));
    }
  }

  void testDivideEqualsScalar()
  {
    M4x3 m;
    for (unsigned int i = 0; i< m.size(); ++i) {
      m[i] = i*1000;
    }
    m /= 100;
    for (unsigned int i = 0; i< m.size(); ++i) {
      CPPUNIT_ASSERT(valueEquality(m[i], M4x4::value_type(i) * 10));
    }
  }

  void testMatrixPlusScalar()
  {
    M4x3 m(11);
    M4x3 m2 = m + 100;
    for (unsigned int i = 0; i< m2.size(); ++i) {
      CPPUNIT_ASSERT(valueEquality(m2, 111));    
    }
  }

  void testMatrixMinusScalar()
  {
    M4x3 m(111);
    M4x3 m2 = m - 101;
    for (unsigned int i = 0; i< m2.size(); ++i) {
      CPPUNIT_ASSERT(valueEquality(m2, 10));    
    }
  }

  void testScalarPlusMatrix()
  {
    M4x3 m(11);
    M4x3 m2 = 100 + m;
    for (unsigned int i = 0; i< m2.size(); ++i) {
      CPPUNIT_ASSERT(valueEquality(m2, 111));    
    }
  }

  void testScalarMinusMatrix()
  {
    M4x3 m(101);
    M4x3 m2 = 111 - m;
    for (unsigned int i = 0; i< m2.size(); ++i) {
      CPPUNIT_ASSERT(valueEquality(m2, 10));    
    }
  }


  void testMatrixTimesScalar()
  {
    M4x3 m(11);
    M4x3 m2 = m * 100;
    for (unsigned int i = 0; i< m2.size(); ++i) {
      CPPUNIT_ASSERT(valueEquality(m2, 1100));    
    }
  }

  void testTranspose()
  {
    M4x3 m;
    for (unsigned int i = 0; i< m.size(); ++i) {
      m[i] = i;
    }
    M3x4 mT = m.transpose();
    for (unsigned int r = 0; r < m.rows(); ++r)
    {
      for (unsigned int c = 0; c < m.cols(); ++c)
      {
        CPPUNIT_ASSERT(valueEquality(m(r,c), mT(c,r)));
      }
    }
  }

  void testLeftInverse()
  {
    for (unsigned int attempt = 0; attempt <5; ++attempt)
    {
      M4x3 m;
      for (unsigned int i = 0; i< m.size(); ++i) {
        m[i] = std::rand()%m.size();
      }
      bool success = true;
      M3x4 mInv = Math::leftInverse(m, success);
      CPPUNIT_ASSERT(success);
      CPPUNIT_ASSERT(Math::equal(mInv*m, M3x3(Math::IdentityMatrix()), 16));
    }
  }

  void testInverse()
  {
    for (unsigned int attempt = 0; attempt <5; ++attempt)
    {
      M3x3 m;
      for (unsigned int i = 0; i< m.size(); ++i) {
        m[i] = std::rand()%m.size();
      }
      bool success = true;
      M3x3 mInv = m.inverse(success);
      CPPUNIT_ASSERT(success);
      CPPUNIT_ASSERT(Math::equal(mInv*m, M3x3(Math::IdentityMatrix()), 16));
    }
  }

  void testInvert()
  {
    for (unsigned int attempt = 0; attempt <5; ++attempt)
    {
      M3x3 m;
      for (unsigned int i = 0; i< m.size(); ++i) {
        m[i] = std::rand()%m.size();
      }
      bool success = true;
      M3x3 mInv = m;
      mInv.invert(success);
      CPPUNIT_ASSERT(success);
      CPPUNIT_ASSERT(Math::equal(mInv*m, M3x3(Math::IdentityMatrix()), 16));
    }
  }



};

#endif
