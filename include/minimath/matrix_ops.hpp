//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MINIMATH_MATRIXOPS_H_
#define MINIMATH_MATRIXOPS_H_

#include <limits>
#include <algorithm>
#include "minimath/numeric_utils.hpp"

//
// Some matrix-matrix operations
// 

namespace minimath {


template <typename T, unsigned int N1, unsigned int N2> class matrix;

///
/// Equality comparison between two matrices.
/// The comparison is element-wise, according to a tolerance level tol:
/// bool equals =  std::abs(b-a) <= tol;
///
/// @param lhs: matrix
/// @param rhs: matrix
/// @param nEpsilon: number of epsilons to be used for tolerance calculation. 
///                  One epsilon is defined as 
///                  std::numeric_limits<T>::epsilon().
///
template <typename T, unsigned int R, unsigned int C>
bool equal(const matrix<T,R,C>& lhs, 
           const matrix<T,R,C>& rhs, 
           unsigned int nEpsilons=0)
{
  typedef typename matrix<T,R,C>::value_type value_type;
  const value_type epsilon = std::numeric_limits<value_type>::epsilon();
  CompareWithTolerance<value_type> comp(nEpsilons*epsilon); 
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(), comp);
}

///
/// Set a row of a matrix to a row vector
///
/// @param m:     matrix whose row will be set
/// @param r:     Row-matrix whose values will be copied into m
/// @param index: Index of the row to set
///
template <typename T, unsigned int R, unsigned int C>
void setRow(minimath::matrix<T,R,C>& m, 
            const minimath::matrix<T, 1, C>& r,
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
/// @param m:     matrix whose column will be set
/// @param r:     Column-matrix whose values will be copied into m
/// @param index: Index of the column to set
///
template <typename T, unsigned int R, unsigned int C>
void setColumn(minimath::matrix<T,R,C>& m, 
               const minimath::matrix<T, R, 1>& c,
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
/// @param m:     matrix whose row will be set
/// @param a:     Array-like object whose values will be copied into m
/// @param index: Index of the row to set
///
template <typename T, unsigned int R, unsigned int C, typename A>
void setRow(minimath::matrix<T,R,C>& m, 
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
/// @param m:     matrix whose column will be set
/// @param a:     Array-like object whose values will be copied into m
/// @param index: Index of the column to set
///
template <typename T, unsigned int R, unsigned int C, typename A>
void setColumn(minimath::matrix<T,R,C>& m, 
               const A& a,
               unsigned int index)
{
  for (unsigned int i = 0; i < R; ++i)
  {
    m(i, index) = a[i];
  }
}

template <typename T, unsigned int N1, unsigned int N2>
matrix<T,N2,N1> left_inverse(const matrix<T,N1,N2>& mat, bool& success)
{
  matrix<T,N2,N1> matT = mat.transpose();
  return ((matT*mat).inverse(success)) * matT;
}

///
/// Find the transformation matrix T such that
/// T * lhs = rhs
/// where lhs is a square matrix
///
template <typename T, unsigned int N>
matrix<T,N> transformation(matrix<T,N> lhs, 
                           const matrix<T,N>& rhs,
                           bool& success)
{
  return rhs*(lhs.inverse(success)); 
}

///
/// Find the transformation matrix T such that
/// T * lhs = rhs
/// where lhs is an N1xN2 matrix and N1>N2

template <typename T, unsigned int N1, unsigned int N2>
matrix<T, N2, N1> transformation(const matrix<T, N1, N2>& ref,
                                 const matrix<T, N2, N2>& meas,
                                 bool& success)
{
  return meas*minimath::left_inverse(ref, success);
}


} // namespace minimath

#endif

