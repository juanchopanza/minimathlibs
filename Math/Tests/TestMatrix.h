//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//

#ifndef TESTS_MATRIX3D_H__
#define TESTS_MATRIX3D_H__


#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Matrix.h"

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
      CPPUNIT_ASSERT(m[i] == i + 100);
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
      CPPUNIT_ASSERT(m[i] == M4x3::value_type(i) - 100);
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
      CPPUNIT_ASSERT(m1[i] == i + 10);
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
      CPPUNIT_ASSERT(m1[i] == 10*(int(i) -1));
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
      CPPUNIT_ASSERT(m[i] == i * 100);
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
      CPPUNIT_ASSERT(m[i] == i * 10);
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

};


namespace {

int test() {

  std::cout << std::boolalpha;

  // instantiate a few matrices

  typedef Math::Matrix<double, 2> M2x2;
  typedef Math::Matrix<double, 3> M3x3;
  typedef Math::Matrix<double, 4> M4x4;
  typedef Math::Matrix<double, 5> M5x5;

  typedef Math::Matrix<double, 2,1> M2x1;
  typedef Math::Matrix<double, 3,2> M3x2;
  typedef Math::Matrix<double, 4,3> M4x3;
  typedef Math::Matrix<double, 5,4> M5x4;
  // Matrix-Matrix operations
  //
  //
  //
  M3x2 m3x2Test;
  M5x4 m5x4Test;

  // in-place subtraction
  m3x2Test -= M3x2(111.);
  std::cout << "In-place subtraction:\n";
  std::cout << m3x2Test << "\n";

  // addition
  m3x2Test = m3x2Test + M3x2(100);
  std::cout << "Addition:\n";
  std::cout << m3x2Test << "\n";

  // subtraction
  m3x2Test = m3x2Test - M3x2(100);
  std::cout << "Subtraction:\n";
  std::cout << m3x2Test << "\n";

  // multiplication : compilation
  // only operations with LHS cols == RHS rows should compile
  M5x5 m5x5Test = M5x5() * M5x5(); 
  std::cout << "Multiplication of default matrices:\n";
  std::cout << m5x5Test << "\n";

  M3x3 m3x3 = m3x2Test * Math::Matrix<double, 2,3>(); 
  std::cout << "Multiplication of default matrices:\n";
  std::cout << m3x3 << "\n";

  M2x2 m2x2 = Math::Matrix<double, 2,3>() * m3x2Test; 
  std::cout << "Multiplication of default matrices:\n";
  std::cout << m2x2 << "\n";

  // multiplication: identity

  for (unsigned int i = 0; i < m5x4Test.size(); ++i) {
    m5x4Test[i] = i;
  }

  std::cout << m5x4Test << "\n";
  M4x4 m4x4Identity = Math::IdentityMatrix();
  std::cout << "Multiplication by 4x4 identity matrix:\n";
  std::cout << (m5x4Test * m4x4Identity) << "\n"; 
  std::cout << "Multiplication by IdentityMatrix (original):\n";
  std::cout << m5x4Test << "\n";

  std::cout << "Multiplication by IdentityMatrix:\n";
  std::cout << (m5x4Test * Math::IdentityMatrix()) << "\n"; 

  std::cout << "Multiplication by IdentityMatrix:\n";
  std::cout << (Math::IdentityMatrix() * m5x4Test) << "\n"; 


  std::cout << "Multiplication by ZeroMatrix:\n";
  std::cout << (Math::ZeroMatrix() * m5x4Test) << "\n"; 
  std::cout << "Multiplication by ZeroMatrix:\n";
  std::cout << (m5x4Test * Math::ZeroMatrix()) << "\n"; 

  M5x5 m5x5_5(5);
  std::cout << "In-place multiplication by IdentityMatrix:\n";
  std::cout << "Reference matrix:\n" << m5x5_5 << "\n";
  m5x5_5 *= M5x5(Math::IdentityMatrix());
  std::cout << m5x5_5 << "\n";
 


  // inversion. Only square matrices smaller than 4x4 should compile
  M3x3 m3x3Inv;
  m3x3Inv.invert();

  M5x5 m5x5Inv;
  //m5x5Inv.invert();

  M2x2 m2x2Test;
  for (unsigned int i = 0; i < m2x2Test.size(); ++i) {
    m2x2Test[i] = i+1;
  }
  M2x2 m2x2InvTest = m2x2Test;
  std::cout << "Invert this matrix:\n" << m2x2Test << "\n";;
  std::cout << m2x2InvTest.invert() << "\n";;
  std::cout << m2x2InvTest << "\n"; 
  std::cout << "Product of matrix with its own inverse:\n";
  std::cout << (m2x2Test*m2x2InvTest) << "\n";


  std::srand(42);
  M3x3 m3x3Test;
  for (unsigned int i = 0; i < m3x3Test.size(); ++i) {
    m3x3Test[i] = std::rand() % m3x3Test.size();
  }
  M3x3 m3x3InvTest = m3x3Test;
  std::cout << "Invert this matrix:\n" << m3x3Test << "\n";;
  std::cout << m3x3InvTest.invert() << "\n";
  std::cout << m3x3InvTest << "\n"; 
  std::cout << "Product of matrix with its own inverse:\n";
  std::cout << (m3x3Test*m3x3InvTest) << "\n";
  std::cout << "Check equality with indentity matrix: ";
  std::cout << ((m3x3Test*m3x3InvTest)==M3x3(Math::IdentityMatrix())) << "\n";
  std::cout << std::numeric_limits<M3x3::value_type>::epsilon() << "\n";

  bool iFlag=true;
  M3x3 m3x3InvTest2 = m3x3Test.inverse(iFlag);
  std::cout << "compare Inverse and Invert: " << iFlag << " " << (m3x3InvTest2==m3x3InvTest) << "\n";

  std::cout << "Multiply and assign by inverse. Reference:\n" 
            << m3x3Test <<"\n";
  m3x3Test *= m3x3InvTest2;
  std::cout << m3x3Test << "\n";

  return 0;
}

}

#endif
