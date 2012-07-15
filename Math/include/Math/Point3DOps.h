//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//


#ifndef MATH_POINT3DOPS_H__
#define MATH_POINT3DOPS_H__

#include <cmath>
#include <limits>


namespace Math {

///
/// Equality comparison between two 3D points.
/// The x, y and z coordinates are compared for equality, , according to a 
/// tolerance level tol:
/// bool equals =  std::abs(x1-x0) <= tol;
///
/// @param lhs: 3D point
/// @param rhs: 3D point
/// @param nEpsilon: number of epsilons to be used for tolerance calculation. 
///                  One epsilon is defined as 
///                  std::numeric_limits<T>::epsilon().
///
template <typename P1, typename P2>
bool equal(const P1& lhs, 
           const P2& rhs,
           unsigned int nEpsilons = 0) 
{
  typedef  typename P1::scalar_type scalar_type;
  scalar_type eps = std::numeric_limits<scalar_type>::epsilon() * nEpsilons;  
  return (std::abs(lhs.x()-rhs.x()) <= eps &&
          std::abs(lhs.y()-rhs.y()) <= eps &&
          std::abs(lhs.z()-rhs.z()) <= eps );
} 

// Square of the magnitude of a point
template <typename P>
typename P::value_type mag2(const P& p) {
  return p.x()*p.x() + p.y()*p.y() + p.z()*p.z();
}

// dot product between two points
template <typename P1, typename P2>
typename P1::value_type dot(const P1& p1, const P2& p2) {
  return p1.x()*p2.x() + p1.y()*p2.y() + p1.z()*p2.z();
}

// distance squared between two points
template <typename P1, typename P2>
typename P1::value_type dist2(const P1& p1, const P2& p2)
{
  const typename P1::value_type diffX = p2.x()-p1.x();
  const typename P1::value_type diffY = p2.y()-p1.y();
  const typename P1::value_type diffZ = p2.z()-p1.z();
  return (diffX*diffX) + (diffY*diffY) + (diffZ*diffZ);
}



}

#endif // MATH_POINT3DOPS_H__
