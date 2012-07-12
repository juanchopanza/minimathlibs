//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//


#ifndef MATH_MATRIXOPS_H__
#define MATH_MATRIXOPS_H__

//
// Some matrix-matrix operations
// 

namespace Math {
  
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

} // namespace Math

#endif

