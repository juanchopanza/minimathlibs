//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
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

