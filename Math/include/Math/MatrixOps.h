//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MATH_MATRIXOPS_H__
#define MATH_MATRIXOPS_H__

#include <limits>

#include "Math/Matrix.h"
#include "Utils.h"

//
// Some matrix-matrix operations
// 

namespace Math {

///
/// Equality comparison between two matrices.
/// The comparison is element-wise, according to a tolerance level tol:
/// bool equals =  std::abs(b-a) <= tol;
///
/// @param lhs: Matrix
/// @param rhs: Matrix
/// @param nEpsilon: number of epsilons to be used for tolerance calculation. 
///                  One epsilon is defined as 
///                  std::numeric_limits<T>::epsilon().
///
template <typename T, unsigned int R, unsigned int C>
bool equal(const Matrix<T,R,C>& lhs, 
           const Matrix<T,R,C>& rhs, 
           unsigned int nEpsilons=0)
{
  typedef typename Matrix<T,R,C>::value_type value_type;
  const value_type epsilon = std::numeric_limits<value_type>::epsilon();
  CompareWithTolerance<value_type> comp(nEpsilons*epsilon); 
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(), comp);
}

///
/// Set a row of a matrix to a row vector
///
/// @param m:     Matrix whose row will be set
/// @param r:     Row-matrix whose values will be copied into m
/// @param index: Index of the row to set
///
template <typename T, unsigned int R, unsigned int C>
void setRow(Math::Matrix<T,R,C>& m, 
            const Math::Matrix<T, 1, C>& r,
            unsigned int index)
{
  for (unsigned int i = 0; i < C; ++i)
  {
    m(index, i) = r(0, i);
  }
}

///
/// Set a column of a matrix to a column vector
///
/// @param m:     Matrix whose column will be set
/// @param r:     Column-matrix whose values will be copied into m
/// @param index: Index of the column to set
///
template <typename T, unsigned int R, unsigned int C>
void setColumn(Math::Matrix<T,R,C>& m, 
               const Math::Matrix<T, R, 1>& c,
               unsigned int index)
{
  for (unsigned int i = 0; i < R; ++i)
  {
    m(i, index) = c(i, 0);
  }
}

///////////////
///
/// Set a row of a matrix to an array-like
///
/// @param m:     Matrix whose row will be set
/// @param a:     Array-like object whose values will be copied into m
/// @param index: Index of the row to set
///
template <typename T, unsigned int R, unsigned int C, typename A>
void setRow(Math::Matrix<T,R,C>& m, 
            const A& a,
            unsigned int index)
{
  for (unsigned int i = 0; i < C; ++i)
  {
    m(index, i) = a[i];
  }
}

///
/// Set a column of a matrix to an array-like object
///
/// @param m:     Matrix whose column will be set
/// @param a:     Array-like object whose values will be copied into m
/// @param index: Index of the column to set
///
template <typename T, unsigned int R, unsigned int C, typename A>
void setColumn(Math::Matrix<T,R,C>& m, 
               const A& a,
               unsigned int index)
{
  for (unsigned int i = 0; i < R; ++i)
  {
    m(i, index) = a[i];
  }
}

///
/// Find the transformation matrix T such that
/// T * lhs = rhs
///
template <typename T, unsigned int N>
Matrix<T,N> transformation(Matrix<T,N> lhs, 
                           const Matrix<T,N>& rhs,
                           bool& success)
{
  return rhs*(lhs.inverse(success)); 
}

} // namespace Math

#endif

