//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//


#ifndef MATH_MATRIXOPS_H__
#define MATH_MATRIXOPS_H__

#include "Math/Matrix.h"

//
// Some matrix-matrix operations
// 

namespace Math {

///
/// Find the transformation matrix T such that
/// T * lhs = rhs
///
template <typename T, typename N>
Matrix<T,N> transformation(Matrix<T,N> lhs, 
                           const Matrix<T,N>& rhs,
                           bool& success)
{
  return rhs*(lhs.inverse(success)); 
}

} // namespace Math

#endif

