//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//



#ifndef MATH_GEOM3DOPS_H__
#define MATH_GEOM3DOPS_H__

#include <tr1/array>
#include <iterator>
#include <iostream>

#include "Math/Rotation3D.h"
#include "Math/Point3D.h"
#include "Math/Translation3D.h"
#include "Math/Transform3D.h"


//
// Helper functions for operations between the Geom3D workd and
// the Matrix world.
//
// @author Juan Palacios juan.palacios.puyana@gmail.com
//

namespace Math {

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
/// Find the transformation matrix T such that
/// T * lhs = rhs
///
template <typename T1, typename T2>
T1 transformation(T1 lhs, 
                  const T2& rhs,
                  bool& success)
{
  return rhs*(lhs.inverse(success)); 
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
template <typename IT>
Transform3D transformation(IT begin, IT end, bool& success)
{
 
  unsigned int length = std::distance(begin, end);
  if (length != 3) {
    std::cerr << "Math::transformation only implemented for 3 poitn system\n";
    return Transform3D();
  }

  Math::Matrix<double,4,3> ref; // 4x3 to allow for rotation + translation
  Math::Matrix<double,3> meas;

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
  Math::setRow(ref, PointXYZD(1,1,1), 3);
  
  // find rotation!
  Matrix<double, 3, 4> rot = transformation(ref, meas, success);
  
  return success ? Transform3D(rot)
                 : Transform3D();

}

}

#endif
