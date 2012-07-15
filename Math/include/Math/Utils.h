//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//


#ifndef MATH_UTILS_H__
#define MATH_UTILS_H__


namespace Math {
 
template <typename T>
struct CompareWithTolerance
{
  CompareWithTolerance() : tol_() {}
  CompareWithTolerance(T tolerance) : tol_(tolerance) {}
  bool operator()(const T& lhs, const T& rhs) const
  {
    return std::abs(rhs-lhs) <= tol_; // <= to allow for 0 tolerance.
  }
 private:
  T tol_;
};

} // namespace Math

#endif // MATH_UTILS_H__
