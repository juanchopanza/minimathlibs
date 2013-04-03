//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MATH_UTILS_H_
#define MATH_UTILS_H_

#include <cstdlib>
#include <cmath>

namespace Math {
 
template <typename T>
bool compareWithTolerance(const T& rhs, const T& lhs, const T& tol)
{
  using std::abs;
  return abs(rhs-lhs) <= tol; // <= to allow for 0 tolerance.
}


template <typename T>
struct CompareWithTolerance
{
  CompareWithTolerance() : tol_() {}
  CompareWithTolerance(T tolerance) : tol_(tolerance) {}
  bool operator()(const T& lhs, const T& rhs) const
  {
    return compareWithTolerance(rhs, lhs, tol_);  
  }
 private:
  T tol_;
};


} // namespace Math

#endif // MATH_UTILS_H_
