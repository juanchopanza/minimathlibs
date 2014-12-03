//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MATH_POINT3D_H_
#define MATH_POINT3D_H_

#include <cmath>
#include <ostream>
#include <limits>
#include "Math/type_traits.hpp"
#include "Math/Point3DOps.h"

namespace Math {

template <typename T>
class Point3D {

 public :

  typedef T scalar_type;
  typedef T value_type;

  Point3D() : data_() {} 
  Point3D(T x, T y, T z)
  {
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
  }

  template <typename P>
  Point3D(const P& rhs)
  {
    data_[0] = rhs.x();
    data_[1] = rhs.y();
    data_[2] = rhs.z();
  } 

  // cartesian coordinate system
  T x() const { return data_[0]; }
  T y() const { return data_[1]; }
  T z() const { return data_[2]; }

  Point3D& x(const value_type& x) 
  { 
    data_[0] = x;
    return *this;
  }

  Point3D& y(const value_type& y) 
  { 
    data_[1] = y;
    return *this;
  }
  Point3D& z(const value_type& z) 
  { 
    data_[2] = z;
    return *this;
  }

  // equality operator
  template <typename Point>
  bool operator==(const Point& rhs) const {
    return equal(*this, rhs, 1);
  }

  // inequality operator
  template <typename Point>
  bool operator!=(const Point& rhs) const {
    return !(*this == rhs);
  }


  // increment
  Point3D& operator += (const Point3D& rhs) {
      data_[0] += rhs.data_[0];
      data_[1] += rhs.data_[1];
      data_[2] += rhs.data_[2];
      return *this;
  }

  // increment, generic XYZ point
  template <typename P>
  typename enable_if<is_point3d<P>::value, Point3D&>::type
  operator += (const P& rhs)
  {
      data_[0] += rhs.x();
      data_[1] += rhs.y();
      data_[2] += rhs.z();
      return *this;
  }
  
  // decrement
  Point3D& operator -= (const Point3D& rhs) {
      data_[0] -= rhs.data_[0];
      data_[1] -= rhs.data_[1];
      data_[2] -= rhs.data_[2];
      return *this;
  }

  // decrement, generic XYZ point
  template <typename P>
  typename enable_if<is_point3d<P>::value, Point3D&>::type
  operator -= (const P& rhs)
  {
      data_[0] -= rhs.x();
      data_[1] -= rhs.y();
      data_[2] -= rhs.z();
      return *this;
  }

  // addition
  Point3D operator+(const Point3D& rhs) const
  {
    return Point3D(data_[0] + rhs.data_[0],
                   data_[1] + rhs.data_[1],
                   data_[2] + rhs.data_[2]);
  }

  // addition, generic XYZ point
  template <typename P>
  typename enable_if<is_point3d<P>::value, Point3D>::type
  operator+(const P& rhs) const {
    return Point3D(data_[0]+rhs.x(), data_[1]+rhs.y(), data_[2]+rhs.z());
  }

  // subtraction
  Point3D operator-(const Point3D& rhs) const
  {
      return Point3D(data_[0] - rhs.data_[0],
                     data_[1] - rhs.data_[1],
                     data_[2] - rhs.data_[2]);
  }


  // subtraction, generic XYZ point
  template <typename P>
  typename enable_if<is_point3d<P>::value, Point3D>::type
  operator-(const P& rhs) const {
    return Point3D(data_[0]-rhs.x(), data_[1]-rhs.y(), data_[2]-rhs.z());
  }

  template <typename Scalar>
  Point3D& operator *= (Scalar rhs) {
    data_[0] *= rhs;
    data_[1] *= rhs;
    data_[2] *= rhs;
    return *this;
  }

  template <typename Scalar>
  Point3D& operator /= (Scalar rhs) {
    data_[0] /= rhs;
    data_[1] /= rhs;
    data_[2] /= rhs;
    return *this;
  }

  // access to underlying data
  T& operator[](unsigned int i) {return data_[i];}

  const T& operator[](unsigned int i) const {return data_[i];}

  // Square of the magnitude of a coordinate
  value_type mag2() const
  {
      return data_[0]*data_[0] + data_[1]*data_[1] + data_[2]*data_[2];
  }

  // normalize coordinates and return original length
  value_type normalize() {
    using std::sqrt;
    value_type d = sqrt(mag2());
    if (equal(d, value_type(0), 1)) return 0;
    operator/=(d);
    return d;
}

 private:
  T data_[3];

};

template <typename T>
std::ostream& operator << (std::ostream& out, const Point3D<T>& point)
{
  return out << "Point3D XYZ( " << point.x() << ", " << point.y() << ", " << point.z() << ")";
}

// addition with foreign vector on LHS
template <typename P, typename T>
typename enable_if<is_point3d<P>::value, Point3D<T> >::type
operator+(const P& lhs, const Point3D<T>&  rhs)
{
  return rhs.operator+(lhs);
}


// scalar multiplication
template <typename T>
Point3D<T> operator*(const Point3D<T>&  point,
                     const typename Point3D<T>::scalar_type& scalar)
{
  Point3D<T> ret(point);
  ret *= scalar;
  return ret;
}

// scalar multiplication
template <typename T>
Point3D<T> operator*(const typename Point3D<T>::scalar_type& scalar,
                     const Point3D<T>&  point)
{
  return point*scalar;
}

// scalar division: only allow Point on LHS
template <typename T>
Point3D<T> operator/(const Point3D<T>&  point,
                     const typename Point3D<T>::scalar_type& scalar)
{
  Point3D<T> ret(point);
  ret /= scalar;
  return ret;
}

typedef Point3D<double> PointXYZD;
typedef Point3D<float> PointXYZF;

} // namespace Math

#endif // MATH_POINT3D_H_
