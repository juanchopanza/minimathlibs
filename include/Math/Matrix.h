//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MATH_MATRIX_H_
#define MATH_MATRIX_H_

//
// Simple class for 2D matrices
// @author : Juan Palacios juan.palacios.puyana@gmail.com
//
//

#include <ostream>
#include <algorithm>
#include "Math/type_traits.hpp"
#include "Math/MatrixInversion.h"
// Matrix data representation class for standard N1*N2 matrix

namespace Math {

struct ZeroMatrix {};

struct IdentityMatrix {};

template <typename T, unsigned int N1, unsigned int N2 = N1>
class Matrix {

 public :

  typedef T value_type;
  typedef T* iterator;
  typedef const T* const_iterator;
 
  enum { ROWS = N1, COLS = N2, SIZE = N1*N2 };

  // implicit construction of zero matrix
  Matrix(const ZeroMatrix&)  : m_data() {}

  // implicit construction of identity matrix
  // to-do disable for non-square matrices
  Matrix(const IdentityMatrix&) : m_data() 
  {
    const unsigned int low = std::min(rows(), cols());
    for (unsigned int i=0; i<low; ++i) {
      operator()(i,i) = value_type(1);
    }
  }

  Matrix() : m_data() {}
  
  // initialize all elements to a given value
  explicit Matrix(const T& val) 
  {
    std::fill(m_data, m_data+SIZE, val);
  } 

  const T& operator()(unsigned int i, unsigned int j) const 
  {
    return m_data[i*N2+j];
  }

  T& operator()(unsigned int i, unsigned int j) 
  {
    return m_data[i*N2+j];
  }

  const T& operator[](unsigned int i) const 
  { 
    return m_data[i];
  } 

  T& operator[](unsigned int i) 
  { 
    return m_data[i];
  } 

  // equality operator
  // to-do add a tolerance for comparison.
  bool operator==(const Matrix& rhs) const 
  {
    return std::equal(begin(), end(), rhs.begin());
  }

  // inequality operator
  bool operator !=(const Matrix& rhs) const 
  {
    return ! operator==(rhs);
  }

  // addition assignemt
  Matrix& operator +=(const Matrix& rhs) 
  {
    std::transform(begin(), end(), 
                   rhs.begin(), begin(), std::plus<value_type>());
    return *this;
  }

  // subtraction assignment
  Matrix& operator -=(const Matrix& rhs) 
  {
    std::transform(begin(), end(), 
                   rhs.begin(), begin(), std::minus<value_type>());
    return *this;
  }

  // multiplication assignment
  // only for square matrices of the same size 
  Matrix& operator*=(const Matrix& rhs) 
  {
    Matrix tmp = (*this) * rhs;
    return operator=(tmp);
  }


  // === element-wise operations involving scalars =========================

  // element-wise addition assignemt of scalar
  template <typename Scalar> 
  Matrix& operator +=(const Scalar& scalar) 
  {
    std::transform(begin(), end(), begin(), 
                   std::bind2nd(std::plus<value_type>(), scalar));
    return *this;
  }

  // element-wise subtraction assignemt of scalar
  template <typename Scalar> 
  Matrix& operator -=(const Scalar& scalar) 
  {
    std::transform(begin(), end(), begin(), 
                   std::bind2nd(std::minus<value_type>(), scalar));
    return *this;

  }

  // element-wise multiplication assignemt of scalar
  template <typename Scalar> 
  Matrix& operator *=(const Scalar& scalar) 
  {
    std::transform(begin(), end(), begin(),
                   std::bind2nd(std::multiplies<value_type>(), scalar));
    return *this;
  }

  // element-wise division assignemt of scalar
  template <typename Scalar> 
  Matrix& operator /=(const Scalar& scalar) 
  {    
    std::transform(begin(), end(), begin(),
                   std::bind2nd(std::divides<value_type>(), scalar));
    return *this;
  }

  // return the transpose of this matrix
  Matrix<T,N2,N1> transpose() const
  {
    Matrix<T,N2,N1> transp;
    for (unsigned int r = 0; r < rows(); ++r)
    {
      for (unsigned int c = 0; c < cols(); ++c)
      {
        transp(c,r) = operator()(r,c);
      }
    }
    return transp;
  }
  // invert the matrix. Return false if inversion fails.
  Matrix& invert(bool& success)
  {
    return detail::MatrixInvertor<T,N1,N2>()(*this, success);
  }

  // return an invrse matrix
  Matrix inverse(bool& success) const 
  {
    return Matrix(*this).invert(success);
  }

  const T* data() const { return m_data; }

  T* data() { return m_data; }

  unsigned int rows() const { return ROWS; }
  unsigned int cols() const { return COLS; }

  // partial standard library container interface

  unsigned int size() const { return SIZE; }
  iterator begin() { return m_data;}
  const_iterator begin() const { return m_data; }
  const_iterator cbegin() { return m_data; }
  const_iterator cbegin() const { return m_data; }

  iterator end() { return m_data + SIZE;}
  const_iterator end() const { return m_data + SIZE; }
  const_iterator cend() { return m_data + SIZE; }
  const_iterator cend() const { return m_data + SIZE; }


 private :

  T m_data[SIZE];

}; // Matrix

// non-member Matrix operations
// multiplication
template <typename T1, typename T2, 
          unsigned int N1, unsigned int N2, unsigned int N3>
Matrix<T1, N1, N3> operator*(const Matrix<T1, N1, N2>& lhs,
                             const Matrix<T2, N2, N3>& rhs) 
{
  Matrix<T1, N1, N3> tmp;
  T1 element;
  for (unsigned int row = 0; row < N1; ++row) {
    for (unsigned int col = 0; col < N3; ++col) {
      element = T1();
      for (unsigned int i = 0; i < N2; ++i) {
        element+= lhs(row,i) * rhs(i,col);
      }
      tmp(row, col) = element; // dot prod of LHS row, RHS col
    }
  }
  return tmp;
}

template <typename T, unsigned int N1, unsigned int N2>
Matrix<T,N1,N2> operator*(const Matrix<T,N1,N2>& lhs, const IdentityMatrix&) 
{
  return lhs;
}

template <typename T, unsigned int N1, unsigned int N2>
Matrix<T,N1,N2> operator*(const IdentityMatrix&, const Matrix<T,N1,N2>& rhs)
{
  return rhs;
}

template <typename T, unsigned int N1, unsigned int N2>
Matrix<T,N1,N2> operator*(const Matrix<T,N1,N2>&, const ZeroMatrix&) 
{
  return ZeroMatrix();
}
template <typename T, unsigned int N1, unsigned int N2>
Matrix<T,N1,N2> operator*(const ZeroMatrix&, const Matrix<T,N1,N2>&) 
{
  return ZeroMatrix();
}


// addition
template <typename T, unsigned int N1, unsigned int N2>
Matrix<T,N1,N2> operator+(const Matrix<T,N1,N2>& lhs, 
                          const Matrix<T,N1,N2>& rhs)
{
  Matrix<T,N1,N2> mat = lhs;
  mat += rhs;
  return mat;
}

// subtraction
template <typename T, unsigned int N1, unsigned int N2>
Matrix<T,N1,N2> operator-(const Matrix<T,N1,N2>& lhs, 
                          const Matrix<T,N1,N2>& rhs)
{
  Matrix<T,N1,N2> mat = lhs;
  mat -= rhs;
  return mat;
}

// ============================================================================
// element-wise operations with scalars

// addition
template <typename T1, unsigned int N1, unsigned int N2, typename T2>
typename enable_if<is_arithmetic<T2>::value, Matrix<T1, N1, N2> >::type
operator+(const Matrix<T1,N1,N2>& lhs, const T2& scalar)
{
  Matrix<T1,N1,N2> mat = lhs;
  mat += scalar;
  return mat;
}

template <typename T1, unsigned int N1, unsigned int N2, typename T2>
typename enable_if<is_arithmetic<T2>::value, Matrix<T1, N1, N2> >::type
operator+(const T2& scalar, const Matrix<T1,N1,N2>& rhs)
{
  Matrix<T1,N1,N2> mat = rhs;
  mat += scalar;
  return mat;
}
// subtraction
template <typename T1, unsigned int N1, unsigned int N2, typename T2>
typename enable_if<is_arithmetic<T2>::value, Matrix<T1, N1, N2> >::type
operator-(const Matrix<T1,N1,N2>& lhs, const T2& scalar)

{
  Matrix<T1,N1,N2> mat = lhs;
  mat -= scalar;
  return mat;
}

template <typename T1, unsigned int N1, unsigned int N2, typename T2>
typename enable_if<is_arithmetic<T2>::value, Matrix<T1, N1, N2> >::type
operator-(const T2& scalar, const Matrix<T1,N1,N2>& rhs)
{
  Matrix<T1,N1,N2> mat = Matrix<T1,N1,N2>(scalar) - rhs;
  return mat;
}
// multiplication
template <typename T1, unsigned int N1, unsigned int N2, typename T2>
typename enable_if<is_arithmetic<T2>::value, Matrix<T1, N1, N2> >::type
operator*(const Matrix<T1,N1,N2>& lhs, const T2& scalar)
{
  Matrix<T1,N1,N2> mat = lhs;
  mat *= scalar;
  return mat;
}

template <typename T1, unsigned int N1, unsigned int N2, typename T2>
typename enable_if<is_arithmetic<T2>::value, Matrix<T1, N1, N2> >::type
operator*(const T2& scalar, const Matrix<T1,N1,N2>& rhs)
{
  return rhs * scalar;
}

// division: only LHS matrix makes sense
template <typename T1, unsigned int N1, unsigned int N2, typename T2>
typename enable_if<is_arithmetic<T2>::value, Matrix<T1, N1, N2> >::type
operator/(const Matrix<T1,N1,N2>& lhs, const T2& scalar)
{
  Matrix<T1,N1,N2> mat = lhs;
  mat /= scalar;
  return mat;
}

// print contents of a matrix.
// works for any matrix with methods
// M::cols();
// M::size();
// and operator []
template <typename M>
std::ostream& print(std::ostream& out, const M& m) 
{
  out << "[\n";
  for (unsigned int i = 0; i < m.size(); ++i) {
    out << " " << m[i];
    if (i%m.cols()==(m.cols()-1))  out << "\n";
  }
  return out << "]\n";
}

template <typename T, 
          unsigned int N1, 
          unsigned int N2>
std::ostream& operator << (std::ostream& out, const Matrix<T,N1,N2>& m) {
  return print(out, m);
}

} // namespace Math

#endif // MATH_MATRIX_H_
