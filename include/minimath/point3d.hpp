//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MINIMATH_POINT3D_H_
#define MINIMATH_POINT3D_H_

#include <cmath>
#include <ostream>
#include <limits>
#include "minimath/type_traits.hpp"
#include "minimath/point3d_ops.hpp"

namespace minimath {

template <typename T>
class point3d {

 public :

  typedef T scalar_type;
  typedef T value_type;

  point3d() : data_() {} 

  point3d(T x, T y, T z)
  {
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
  }

  template <typename P>
  point3d(const P& rhs)
  {
    data_[0] = rhs.x();
    data_[1] = rhs.y();
    data_[2] = rhs.z();
  } 

  // cartesian coordinate system
  T x() const { return data_[0]; }
  T y() const { return data_[1]; }
  T z() const { return data_[2]; }

  point3d& x(const value_type& x) 
  { 
    data_[0] = x;
    return *this;
  }

  point3d& y(const value_type& y) 
  { 
    data_[1] = y;
    return *this;
  }
  point3d& z(const value_type& z) 
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
  point3d& operator += (const point3d& rhs) {
      data_[0] += rhs.data_[0];
      data_[1] += rhs.data_[1];
      data_[2] += rhs.data_[2];
      return *this;
  }

  // increment, generic XYZ point
  template <typename P>
  typename enable_if<is_point3d<P>::value, point3d&>::type
  operator += (const P& rhs)
  {
      data_[0] += rhs.x();
      data_[1] += rhs.y();
      data_[2] += rhs.z();
      return *this;
  }
  
  // decrement
  point3d& operator -= (const point3d& rhs) {
      data_[0] -= rhs.data_[0];
      data_[1] -= rhs.data_[1];
      data_[2] -= rhs.data_[2];
      return *this;
  }

  // decrement, generic XYZ point
  template <typename P>
  typename enable_if<is_point3d<P>::value, point3d&>::type
  operator -= (const P& rhs)
  {
      data_[0] -= rhs.x();
      data_[1] -= rhs.y();
      data_[2] -= rhs.z();
      return *this;
  }

  // addition
  point3d operator+(const point3d& rhs) const
  {
    return point3d(data_[0] + rhs.data_[0],
                   data_[1] + rhs.data_[1],
                   data_[2] + rhs.data_[2]);
  }

  // addition, generic XYZ point
  template <typename P>
  typename enable_if<is_point3d<P>::value, point3d>::type
  operator+(const P& rhs) const {
    return point3d(data_[0]+rhs.x(), data_[1]+rhs.y(), data_[2]+rhs.z());
  }

  // subtraction
  point3d operator-(const point3d& rhs) const
  {
      return point3d(data_[0] - rhs.data_[0],
                     data_[1] - rhs.data_[1],
                     data_[2] - rhs.data_[2]);
  }


  // subtraction, generic XYZ point
  template <typename P>
  typename enable_if<is_point3d<P>::value, point3d>::type
  operator-(const P& rhs) const {
    return point3d(data_[0]-rhs.x(), data_[1]-rhs.y(), data_[2]-rhs.z());
  }

  template <typename Scalar>
  point3d& operator *= (Scalar rhs) {
    data_[0] *= rhs;
    data_[1] *= rhs;
    data_[2] *= rhs;
    return *this;
  }

  template <typename Scalar>
  point3d& operator /= (Scalar rhs) {
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
std::ostream& operator << (std::ostream& out, const point3d<T>& point)
{
  return out << "point3d XYZ( " << point.x() << ", " << point.y() << ", " << point.z() << ")";
}

// addition with foreign vector on LHS
template <typename P, typename T>
typename enable_if<is_point3d<P>::value, point3d<T> >::type
operator+(const P& lhs, const point3d<T>&  rhs)
{
  return rhs.operator+(lhs);
}


// scalar multiplication
template <typename T>
point3d<T> operator*(const point3d<T>&  point,
                     const typename point3d<T>::scalar_type& scalar)
{
  point3d<T> ret(point);
  ret *= scalar;
  return ret;
}

// scalar multiplication
template <typename T>
point3d<T> operator*(const typename point3d<T>::scalar_type& scalar,
                     const point3d<T>&  point)
{
  return point*scalar;
}

// scalar division: only allow Point on LHS
template <typename T>
point3d<T> operator/(const point3d<T>&  point,
                     const typename point3d<T>::scalar_type& scalar)
{
  point3d<T> ret(point);
  ret /= scalar;
  return ret;
}

typedef point3d<double> pointxyzd;
typedef point3d<float> pointxyzf;

} // namespace Math

#endif // MINIMATH_POINT3D_H_
