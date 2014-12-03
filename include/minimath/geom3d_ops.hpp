//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//



#ifndef MINIMATH_GEOM3DOPS_H_
#define MINIMATH_GEOM3DOPS_H_

#include <iterator>
#include <iostream>

#include "minimath/type_traits.hpp"
#include "minimath/point3d.hpp"
#include "minimath/matrix.hpp"
#include "minimath/matrix_ops.hpp"


//
// Helper functions for operations between the Geom3D world and
// the matrix world.
//
// @author Juan Palacios juan.palacios.puyana@gmail.com
//

namespace minimath {

// Forward declarations of class templates that depend on point3d and matrix.
template <typename T> class axisangle;
template <typename T> class rotation3d;
template <typename T> class translation3d;
template <typename T> class transform3d;


// implementation specific helpers
namespace detail
{
template <typename T, typename P>
transform3d<T> transformation1(const P& pointPair)
{
  return transform3d<T>(translation3d<T>(pointPair[1]-pointPair[0]));
}

template <typename T, typename P>
transform3d<T> transformation2(const P& pair0, const P& pair1, bool& success)
{

  // direction vectors
  point3d<T> v0 = pair1[0] - pair0[0]; // reference points
  point3d<T> v1 = pair1[1] - pair0[1]; // measured points

  minimath::point3d<T> axis = minimath::cross(v0, v1);
  const T mag2Axis = minimath::mag2(axis);
  const T normalFactor2 = minimath::mag2(v0)*minimath::mag2(v1);
  if (normalFactor2 <=0.) {
    success = false;
    return transform3d<T>();
  }
  const double sinAngle = std::sqrt(mag2Axis/normalFactor2);
  const double angle = std::asin(sinAngle);
  minimath::translation3d<T> originInv(pair0[0]);
  minimath::translation3d<T> origin(originInv.inverse());
  minimath::transform3d<T> trans(rotation3d<T>(minimath::axisangle<T>(axis, angle)), 
                            minimath::translation3d<T>(pair0[1]-pair0[0]));
  return transform3d<T>(originInv)*(trans*transform3d<T>(origin));
}

template <typename T, typename IT>
transform3d<T> transformation3(IT begin, IT end, bool& success)
{

  minimath::matrix<T,4,3> ref; // 4x3 to allow for rotation + translation
  minimath::matrix<T,3> meas;

  unsigned int index = 0;

  // to-do write something to assign elements to matrix
  for (IT iPair = begin; iPair !=end; ++iPair)
  {
    for (unsigned int i = 0; i < 3; ++i)
    {
      ref(i, index) = (*iPair)[0][i];
      meas(i, index) = (*iPair)[1][i];
    }
    ++index;
  }
  minimath::setRow(ref, point3d<T>(1,1,1), 3);
  
  // find rotation!
  matrix<T, 3, 4> rot = transformation(ref, meas, success);
  
  return success ? transform3d<T>(rot) : transform3d<T>();

}

} // namespace detail

// multiplication between a 3x3 matrix and a 3D point
template <typename T>
point3d<T> operator*(const matrix<T,3>& rot, 
                     const point3d<T>& point) 
{
  double elements[3];
  for (unsigned int row = 0; row < 3; ++row) {
    double element = 0;
    for (unsigned int i = 0; i < 3; ++i) {
      element+= rot(row,i) * point[i];
    }
    elements[row] = element; // dot prod of LHS row, RHS col
  }
  return point3d<T> (elements[0], elements[1], elements[2]);

} 

// multiplication between a 3x3 matrix and a generic 3D point
// Use SFINAE accept only types with members x, y, z
template <typename Point, typename T>
typename enable_if<is_point3d<Point>::value, Point>::type
operator*(const matrix<T,3>& rot, const Point&  point)
{
  double elements[3];
  for (unsigned int i = 0; i < 3; ++i)
      elements[i] = rot(i, 0)*point.x() + rot(i,1)*point.y() + rot(i,2)*point.z();

  return Point(elements[0], elements[1], elements[2]);
}


// Multiplication between a 3x4 matrix and a 3D point
// The 4th column represents the translation
template <typename T>
point3d<T> operator*(const matrix<T,3,4>& rot, 
                     const point3d<T>& point) 
{
  double elements[3];
  for (unsigned int row = 0; row < 3; ++row) {
    double element = 0;
    for (unsigned int i = 0; i < 3; ++i) {
      element+= rot(row,i) * point[i];
    }
    elements[row] = element + rot(row,3); // dot prod of LHS row, RHS col
  }
  return point3d<T> (elements[0], elements[1], elements[2]);

} 

// Multiplication between a 3x4 matrix and a 3D point
// The 4th column represents the translation
// Use SFINAE accept only types with members x, y, z
template <typename Point, typename T>
typename enable_if<is_point3d<Point>::value, Point>::type
operator*(const matrix<T,3,4>& rot,
          const Point&  point)
{
  double elements[3];
  for (unsigned int i = 0; i < 3; ++i)
      elements[i] = rot(i, 0)*point.x() + rot(i,1)*point.y() + rot(i,2)*point.z() + rot(i,3);

  return Point(elements[0], elements[1], elements[2]);
}


///
/// Find the 3D transformation that maps a set of points P to 
/// a set of points P'
/// The points must be paired up in a sequence, such that each element of
/// the sequence contains p and p'. The pairs must make the points accessible
/// via operator[](size_t) such that, for a given element,
///
/// elem[0] is the reference point
/// elem[1] is the transformed point
/// elem[1][2] is the third component of the transformed point
///
/// @param begin   : forward iterator at start of point pair sequence
/// @param end     : forward iterator one past the end of point pair sequence
/// @param success : boolean success flag
/// @return        : transform3d with transformation. Identits transformation
///                  if procesure fails.
///
template <typename T, typename IT>
transform3d<T> transformation(IT begin, IT end, bool& success)
{
  typename std::iterator_traits<IT>::difference_type length = std::distance(begin, end);
  if (length == 3) return detail::transformation3<T>(begin, end, success);
  if (length == 2) 
  {
    IT second = begin + 1;
    return detail::transformation2<T>(*begin, *second, success);
  }
  if (length == 1) return detail::transformation1<T>(*begin);
  std::cerr << "minimath::transformation only implemented for 1, 2 and 3 point systems. Received "
      << length <<" point pairs\n";
  return transform3d<T>();
}

}

#endif
