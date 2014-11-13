//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//



#ifndef MATH_GEOM3DOPS_H_
#define MATH_GEOM3DOPS_H_

#include <iterator>
#include <iostream>

#include "Math/Point3D.h"
#include "Math/Matrix.h"
#include "Math/MatrixOps.h"


//
// Helper functions for operations between the Geom3D workd and
// the Matrix world.
//
// @author Juan Palacios juan.palacios.puyana@gmail.com
//

namespace Math {

// Forward declarations of class templates that depend on Point3D and Matrix.
template <typename T> class AxisAngle;
template <typename T> class Rotation3D;
template <typename T> class Translation3D;
template <typename T> class Transform3D;


// implementation specific helpers
namespace detail
{
template <typename T, typename P>
Transform3D<T> transformation1(const P& pointPair)
{
  return Transform3D<T>(Translation3D<T>(pointPair[1]-pointPair[0]));
}

template <typename T, typename P>
Transform3D<T> transformation2(const P& pair0, const P& pair1, bool& success)
{

  // direction vectors
  Point3D<T> v0 = pair1[0] - pair0[0]; // reference points
  Point3D<T> v1 = pair1[1] - pair0[1]; // measured points

  Math::Point3D<T> axis = Math::cross(v0, v1);
  const T mag2Axis = Math::mag2(axis);
  const T normalFactor2 = Math::mag2(v0)*Math::mag2(v1);
  if (normalFactor2 <=0.) {
    success = false;
    return Transform3D<T>();
  }
  const double sinAngle = std::sqrt(mag2Axis/normalFactor2);
  const double angle = std::asin(sinAngle);
  Math::Translation3D<T> originInv(pair0[0]);
  Math::Translation3D<T> origin(originInv.inverse());
  Math::Transform3D<T> trans(Rotation3D<T>(Math::AxisAngle<T>(axis, angle)), 
                            Math::Translation3D<T>(pair0[1]-pair0[0]));
  return Transform3D<T>(originInv)*(trans*Transform3D<T>(origin));
}

template <typename T, typename IT>
Transform3D<T> transformation3(IT begin, IT end, bool& success)
{

  Math::Matrix<T,4,3> ref; // 4x3 to allow for rotation + translation
  Math::Matrix<T,3> meas;

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
  Math::setRow(ref, Point3D<T>(1,1,1), 3);
  
  // find rotation!
  Matrix<T, 3, 4> rot = transformation(ref, meas, success);
  
  return success ? Transform3D<T>(rot) : Transform3D<T>();

}

} // namespace detail

// multiplication between a 3x3 matrix and a 3D point
template <typename T, template <typename> class C>
Point3D<T, C> operator*(const Matrix<T,3>& rot, 
                        const Point3D<T, C>&  point) 
{
  double elements[3];
  for (unsigned int row = 0; row < 3; ++row) {
    double element = 0;
    for (unsigned int i = 0; i < 3; ++i) {
      element+= rot(row,i) * point[i];
    }
    elements[row] = element; // dot prod of LHS row, RHS col
  }
  return Point3D<T, C> (elements[0], elements[1], elements[2]);

} 

// Multiplication between a 3x4 matrix and a 3D point
// The 4th column represents the translation
template <typename T, template <typename> class C>
Point3D<T, C> operator*(const Matrix<T,3,4>& rot, 
                        const Point3D<T, C>&  point) 
{
  double elements[3];
  for (unsigned int row = 0; row < 3; ++row) {
    double element = 0;
    for (unsigned int i = 0; i < 3; ++i) {
      element+= rot(row,i) * point[i];
    }
    elements[row] = element + rot(row,3); // dot prod of LHS row, RHS col
  }
  return Point3D<T, C> (elements[0], elements[1], elements[2]);

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
/// @return        : Transform3D with transformation. Identits transformation
///                  if procesure fails.
///
template <typename T, typename IT>
Transform3D<T> transformation(IT begin, IT end, bool& success)
{
  typename std::iterator_traits<IT>::difference_type length = std::distance(begin, end);
  if (length == 3) return detail::transformation3<T>(begin, end, success);
  if (length == 2) return detail::transformation2<T>(*begin, *(++begin), success);
  if (length == 1) return detail::transformation1<T>(*begin);
  std::cerr << "Math::transformation only implemented for 1, 2 and 3 point systems. Received " << length <<" point pairs\n";
  return Transform3D<T>();
}

}

#endif
