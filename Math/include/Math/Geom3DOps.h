//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//



#ifndef MATH_GEOM3DOPS_H__
#define MATH_GEOM3DOPS_H__

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


// multiplication between a 3x3 matrix and a 3D point
template <typename T>
Translation3D operator*(const Matrix<T,3>& rot, 
                        const Translation3D&  point) 
{
  typedef Translation3D::vector_type vector_type_;
  double elements[3];
  for (unsigned int row = 0; row < 3; ++row) {
    double element = 0;
    for (unsigned int i = 0; i < 3; ++i) {
      element+= rot(row,i) * point[i];
    }
    elements[row] = element; // dot prod of LHS row, RHS col
  }
  return Translation3D(vector_type_(elements[0], elements[1], elements[2]));

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

template <typename T, unsigned int N1, unsigned int N2>
Matrix<T,N1,N2> transformationX(Matrix<T,N1,N2> lhs, 
                               const Matrix<T,N2>& rhs,
                               bool& success)
{
  return lhs*(rhs.inverse(success)); 
}



//
// Utils to find 3D alignment from 3 reference points and 3 measured points
//

Transform3D transformation(std::pair<PointXYZD, PointXYZD> p0,
                           std::pair<PointXYZD, PointXYZD> p1,
                           std::pair<PointXYZD, PointXYZD> p2,
                           bool& success)
{
  // shift by position of one
  PointXYZD transl = p0.second - p0.first;
  // shift all measured points
  p0.second -= transl;
  p1.second -= transl;
  p2.second -= transl;

  Translation3D toOrigin(p0.first*-1);

  // move all points to origin
  p0.first = toOrigin*p0.first;
  p1.first = toOrigin*p1.first;
  p2.first = toOrigin*p2.first;

  p0.second = toOrigin*p0.second;
  p1.second = toOrigin*p1.second;
  p2.second = toOrigin*p2.second;

  Math::Matrix<double,3,3> ref; // 4x3 to allow for rotation + translation
  Math::setColumn(ref, p0.first, 0);
  Math::setColumn(ref, p1.first, 1);
  Math::setColumn(ref, p2.first, 2);
//  Math::setRow(ref, PointXYZD(1,1,1), 3);
  std::cout << "\nReference matrix:\n" << ref << "\n";

  Math::Matrix<double,3> meas;
  Math::setColumn(meas, p0.second, 0);
  Math::setColumn(meas, p1.second, 1);
  Math::setColumn(meas, p2.second, 2);
  std::cout << "\nMeasured matrix:\n" << meas << "\n";

  // find rotation!
  Matrix<double,3,3> rot = transformation(ref, meas, success);

  std::cout << "Success? "<< success << "\nRotation matrix:\n" << rot << "\n";
  return success ? Transform3D()
                 : Transform3D();

}

}

#endif
