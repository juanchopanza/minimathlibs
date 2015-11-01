//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestMatrix
#include <boost/test/unit_test.hpp>

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include "minimath/matrix.hpp"
#include "minimath/matrix_ops.hpp"
#include "minimath/numeric_utils.hpp"

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


typedef minimath::matrix<double, 2> M2x2;
typedef minimath::matrix<double, 3> M3x3;
typedef minimath::matrix<double, 4> M4x4;
typedef minimath::matrix<double, 5> M5x5;

typedef minimath::matrix<double, 2,1> M2x1;
typedef minimath::matrix<double, 3,2> M3x2;
typedef minimath::matrix<double, 4,3> M4x3;
typedef minimath::matrix<double, 5,4> M5x4;

typedef minimath::matrix<double, 3,4> M3x4;
typedef minimath::matrix<double, 4,5> M4x5;

BOOST_AUTO_TEST_SUITE(TestMatrix)


BOOST_AUTO_TEST_CASE(testDefaultConstruction)
{
  M2x2 a;
  M2x2 b;
  M2x2 c;
  BOOST_CHECK(valueEquality(a, 0.));
  BOOST_CHECK(valueEquality(b, 0.));
  BOOST_CHECK(valueEquality(c, 0.));
  BOOST_CHECK(2==a.rows());
  BOOST_CHECK(2==a.cols());
  BOOST_CHECK(4==a.size());
  BOOST_CHECK(a==b);
  BOOST_CHECK(a==c);
  BOOST_CHECK(b==c);

  M5x4 d, e, f;
  BOOST_CHECK(valueEquality(d, 0));
  BOOST_CHECK(valueEquality(e, 0));
  BOOST_CHECK(valueEquality(f, 0));
  BOOST_CHECK(5==e.rows());
  BOOST_CHECK(4==e.cols());
  BOOST_CHECK(20==e.size());
  BOOST_CHECK(d==e);
  BOOST_CHECK(d==f);
  BOOST_CHECK(e==f);

}

BOOST_AUTO_TEST_CASE(testZeroMatrixConstruction)
{
  M4x3 m = minimath::zero_matrix();
  BOOST_CHECK(valueEquality(m, 0));
}

BOOST_AUTO_TEST_CASE(testZeroMatrixAssignment)
{
  M4x3 m;
  m = minimath::zero_matrix();
  BOOST_CHECK(valueEquality(m, 0));
}


BOOST_AUTO_TEST_CASE(testIdentityMatrixConstruction)
{
  M4x4 m4 = minimath::identity_matrix();
  BOOST_CHECK(isIdentity(m4));
  M5x5 m5 = minimath::identity_matrix();
  BOOST_CHECK(isIdentity(m5));

}

BOOST_AUTO_TEST_CASE(testIdentityMatrixAssignment)
{
  M4x4 m;
  m = minimath::identity_matrix();
  BOOST_CHECK(isIdentity(m));
}


BOOST_AUTO_TEST_CASE(testScalarConstruction)
{
  for (int  i = -20; i < 21; ++i) {
    M5x5 m(i);
    BOOST_CHECK(valueEquality(m, i));
  }
}

BOOST_AUTO_TEST_CASE(testCopyConstruction)
{
  M4x3 m;
  for (unsigned int i = 0; i< m.size(); ++i) {
    m[i] = i;
  }
  M4x3 m2(m);
  BOOST_CHECK(m2==m);
}

BOOST_AUTO_TEST_CASE(testAssignment)
{
  M4x3 m;
  for (unsigned int i = 0; i< m.size(); ++i) {
    m[i] = i;
  }
  M4x3 m2;
  m2 = m;
  BOOST_CHECK(m2==m);

}

BOOST_AUTO_TEST_CASE(testEquality)
{
  M4x3 m1, m2;
  for (unsigned int i = 0; i< m1.size(); ++i) {
    m1[i] = i;
    m2[i] = i;
  }
  BOOST_CHECK(m2==m1);

}

BOOST_AUTO_TEST_CASE(testInequality)
{
  M4x3 m;
  for (unsigned int i = 0; i< m.size(); ++i) {
    m[i] = i;
  }
  M4x3 m2;
  BOOST_CHECK(m2!=m);
}


BOOST_AUTO_TEST_CASE(testPlusEqualsScalar)
{
  M4x3 m;
  for (unsigned int i = 0; i< m.size(); ++i) {
    m[i] = i;
  }
  m += 100;
  for (unsigned int i = 0; i< m.size(); ++i) {
    BOOST_CHECK(valueEquality(m[i], M4x3::value_type(i) + 100));
  }
}

BOOST_AUTO_TEST_CASE(testMinusEqualsScalar)
{
  M4x3 m;
  for (unsigned int i = 0; i< m.size(); ++i) {
    m[i] = i;
  }
  m -= 100;
  for (unsigned int i = 0; i< m.size(); ++i) {
    BOOST_CHECK(valueEquality(m[i], M4x3::value_type(i) - 100.));
  }
}

BOOST_AUTO_TEST_CASE(testPlusEquals)
{
  M3x3 m1;
  for (unsigned int i = 0; i< m1.size(); ++i) {
    m1[i] = i;
  }
  M3x3 m2(10);
  m1 += m2;
  for (unsigned int i = 0; i< m1.size(); ++i) {
    BOOST_CHECK(valueEquality(m1[i], M3x3::value_type(i) + 10));
  }

}

BOOST_AUTO_TEST_CASE(testMinusEquals)
{
  M3x3 m1;
  for (unsigned int i = 0; i< m1.size(); ++i) {
    m1[i] = 10*i;
  }
  M3x3 m2(10);
  m1 -= m2;
  for (unsigned int i = 0; i< m1.size(); ++i) {
    BOOST_CHECK(valueEquality(m1[i], M3x3::value_type(10)*(int(i) -1) ));
  }
}

BOOST_AUTO_TEST_CASE(testTimesEqualsScalar)
{
  M4x3 m;
  for (unsigned int i = 0; i< m.size(); ++i) {
    m[i] = i;
  }
  m *= 100;
  for (unsigned int i = 0; i< m.size(); ++i) {
    BOOST_CHECK(valueEquality(m[i], M4x3::value_type(i) * 100));
  }
}

BOOST_AUTO_TEST_CASE(testDivideEqualsScalar)
{
  M4x3 m;
  for (unsigned int i = 0; i< m.size(); ++i) {
    m[i] = i*1000;
  }
  m /= 100;
  for (unsigned int i = 0; i< m.size(); ++i) {
    BOOST_CHECK(valueEquality(m[i], M4x4::value_type(i) * 10));
  }
}

BOOST_AUTO_TEST_CASE(testMatrixPlusScalar)
{
  M4x3 m(11);
  M4x3 m2 = m + 100;
  for (unsigned int i = 0; i< m2.size(); ++i) {
    BOOST_CHECK(valueEquality(m2, 111));    
  }
}

BOOST_AUTO_TEST_CASE(testMatrixMinusScalar)
{
  M4x3 m(111);
  M4x3 m2 = m - 101;
  for (unsigned int i = 0; i< m2.size(); ++i) {
    BOOST_CHECK(valueEquality(m2, 10));    
  }
}

BOOST_AUTO_TEST_CASE(testScalarPlusMatrix)
{
  M4x3 m(11);
  M4x3 m2 = 100 + m;
  for (unsigned int i = 0; i< m2.size(); ++i) {
    BOOST_CHECK(valueEquality(m2, 111));    
  }
}

BOOST_AUTO_TEST_CASE(testScalarMinusMatrix)
{
  M4x3 m(101);
  M4x3 m2 = 111 - m;
  for (unsigned int i = 0; i< m2.size(); ++i) {
    BOOST_CHECK(valueEquality(m2, 10));    
  }
}


BOOST_AUTO_TEST_CASE(testMatrixTimesScalar)
{
  M4x3 m(11);
  M4x3 m2 = m * 100;
  for (unsigned int i = 0; i< m2.size(); ++i) {
    BOOST_CHECK(valueEquality(m2, 1100));    
  }
}

BOOST_AUTO_TEST_CASE(testTranspose)
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
      BOOST_CHECK(valueEquality(m(r,c), mT(c,r)));
    }
  }
}

BOOST_AUTO_TEST_CASE(testLeftInverse)
{
  for (unsigned int attempt = 0; attempt <5; ++attempt)
  {
    M4x3 m;
    for (unsigned int i = 0; i< m.size(); ++i) {
      m[i] = std::rand()%m.size();
    }
    bool success = true;
    M3x4 mInv = minimath::left_inverse(m, success);
    BOOST_CHECK(success);
    BOOST_CHECK(minimath::equal(mInv*m, M3x3(minimath::identity_matrix()), 128));
  }
}

BOOST_AUTO_TEST_CASE(testInverse)
{
  for (unsigned int attempt = 0; attempt <5; ++attempt)
  {
    M3x3 m;
    for (unsigned int i = 0; i< m.size(); ++i) {
      m[i] = std::rand()%m.size();
    }
    bool success = true;
    M3x3 mInv = m.inverse(success);
    BOOST_CHECK(success);
    BOOST_CHECK(minimath::equal(mInv*m, M3x3(minimath::identity_matrix()), 128));
  }
}

BOOST_AUTO_TEST_CASE(testInvert)
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
    BOOST_CHECK(success);
    BOOST_CHECK(minimath::equal(mInv*m, M3x3(minimath::identity_matrix()), 16));
  }
}

BOOST_AUTO_TEST_SUITE_END()
