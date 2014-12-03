//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimath.
// Subject to the BSD 2-Clause License
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MINIMATH_ROTATION3D_H_
#define MINIMATH_ROTATION3D_H_

#include "minimath/point3d.hpp"
#include "minimath/matrix.hpp"
#include "minimath/matrix_ops.hpp"
#include "minimath/geom3d_ops.hpp"
#include "minimath/numeric_utils.hpp"
#include <cmath>

namespace minimath {

namespace detail
{

template <typename T>
inline matrix<T,3,3> rotX(T cosA, T sinA)
{
  matrix<T,3,3> rot = identity_matrix();
  rot(1,1) =  cosA;
  rot(2,2) =  cosA;
  rot(1,2) = -sinA;
  rot(2,1) =  sinA;
  return rot;

}

template <typename T>
inline matrix<T,3,3> rotY(T cosA, T sinA)
{
  matrix<T,3,3> rot = identity_matrix();
  rot(0,0) =  cosA;
  rot(2,2) =  cosA;
  rot(2,0) = -sinA;
  rot(0,2) =  sinA;
  return rot;
}

template <typename T>
inline matrix<T,3,3> rotZ(T cosA, T sinA)
{
  matrix<T,3,3> rot = identity_matrix();
  rot(0,0) =  cosA;
  rot(1,1) =  cosA;
  rot(0,1) = -sinA;
  rot(1,0) =  sinA;
  return rot;
}

template <typename T, typename V>
matrix<T,3,3> axisangle_(V axis, T cosA, T sinA)
{
  T mag = std::sqrt(minimath::mag2(axis));
  axis /= mag;

  matrix<T,3,3> rot;

  const T cosComp = 1. - cosA;
  const T x = axis[0];
  const T y = axis[1];
  const T z = axis[2];

  rot(0,0) = cosComp * x * x  +  cosA;
  rot(0,1) = cosComp * x * y  -  sinA * z;
  rot(0,2) = cosComp * x * z  +  sinA * y;
  rot(1,0) = cosComp * y * x  +  sinA * z;
  rot(1,1) = cosComp * y * y  +  cosA;
  rot(1,2) = cosComp * y * z  -  sinA * x;
  rot(2,0) = cosComp * z * x  -  sinA * y;
  rot(2,1) = cosComp * z * y  +  sinA * x;
  rot(2,2) = cosComp * z * z  +  cosA;

  return rot;
}


} // namespace detail

/// create a 3x3 matrix representing a rotation of alpha radians
/// about the X axis
template <typename T>
inline matrix<T,3,3> rotationX(T alpha)
{
  const T c = std::cos(alpha);
  const T s = std::sin(alpha);
  return detail::rotX(c, s);
}

/// create a 3x3 matrix representing a rotation of alpha radians
/// about the Y axis
template <typename T>
inline matrix<T,3,3> rotationY(T alpha)
{
  //matrix<T,3,3> rot = identity_matrix();
  const T c = std::cos(alpha);
  const T s = std::sin(alpha);
  return detail::rotY(c, s);
}

/// create a 3x3 matrix representing a rotation of alpha radians
/// about the Z axis
template <typename T>
inline matrix<T,3,3> rotationZ(T alpha)
{
  //matrix<T,3,3> rot = identity_matrix();
  const T c = std::cos(alpha);
  const T s = std::sin(alpha);
  return detail::rotZ(c,s);
}

/// create a 3x3 matrix representing a rotation of alpha radians
/// about an axis
template <typename T, typename Axis>
matrix<T,3,3> make_axis_angle(const Axis& axis, T alpha)
{
  //matrix<T,3,3> rot = identity_matrix();
  const T c = std::cos(alpha);
  const T s = std::sin(alpha);
  return detail::axisangle_(axis, c, s);
}


template <typename T>
class axisanglebase {

 public:

  axisanglebase() : m_sin(0), m_cos(1) {}
  explicit axisanglebase(T angle)
  :
  m_sin(std::sin(angle)), m_cos(std::cos(angle)) {}

  T cosAlpha() const { return m_cos; };
  T sinAlpha() const { return m_sin; };

  bool operator==(const axisanglebase& rhs) const {
    return (compare_with_tolerance(m_sin, rhs.sinAlpha(), T()) &&
            compare_with_tolerance(m_cos, rhs.cosAlpha(), T()));
  }
  axisanglebase& invert(bool& success)
  {
    m_sin *= -1;
    success = true;
    return *this;
  }
 private:
  T m_sin, m_cos;
};

/// Simple class representing a rotation about an
/// axis.
template <typename T>
class axisangle : public axisanglebase<T> {

 public:

  typedef point3d<T> axis_type;

 public:

  axisangle() : axisanglebase<T>(), m_axis(0,0,1) {}

  axisangle(const axis_type& axis) : axisanglebase<T>(), m_axis(axis) {}

  axisangle(T angle) : axisanglebase<T>(angle), m_axis() {}

  axisangle(const axis_type& axis, T angle)
  :
  axisanglebase<T>(angle),
  m_axis(axis)
  {
  }

  const axis_type& axis() const { return m_axis; }

  axisangle& invert(bool& success)
  {
    axisanglebase<T>::invert(success);
    return *this;
  }
  axisangle inverse(bool& success) const
  {
    axisangle inv(*this);
    inv.invert(success);
    return inv;
  }


 private:

  axis_type m_axis;

};

// rotation about the X axis
template <typename T>
class rotation3dx  : public axisanglebase<T> {

 public:
  rotation3dx() : axisanglebase<T>() {}
  explicit rotation3dx(T angle) : axisanglebase<T>(angle) {}
  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation
    return Point(point.x(),
                 this->cosAlpha()*point.y() - this->sinAlpha()*point.z(),
                 this->cosAlpha()*point.z() + this->sinAlpha()*point.y() );
  }

  rotation3dx& invert(bool& success)
  {
    axisanglebase<T>::invert(success);
    return *this;
  }
  rotation3dx inverse(bool& success) const
  {
    rotation3dx inv(*this);
    inv.invert(success);
    return inv;
  }

};

// rotation about the Y axis
template <typename T>
class rotation3dy : public axisanglebase<T> {

 public:
  rotation3dy() : axisanglebase<T>() {}
  explicit rotation3dy(T angle) : axisanglebase<T>(angle) {}

  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation
    return Point(this->cosAlpha()*point.x() + this->sinAlpha()*point.z(),
                 point.y(),
                 this->cosAlpha()*point.z() - this->sinAlpha()*point.x() );
  }

  rotation3dy& invert(bool& success)
  {
    axisanglebase<T>::invert(success);
    return *this;
  }

  rotation3dy inverse(bool& success) const
  {
    rotation3dy inv(*this);
    inv.invert(success);
    return inv;
  }

};

// rotation about the Z axis
template <typename T>
class rotation3dz : public axisanglebase<T> {

 public:
  rotation3dz() : axisanglebase<T>() {}
  explicit rotation3dz(T angle) : axisanglebase<T>(angle) {}

  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation
    return Point(this->cosAlpha()*point.x() - this->sinAlpha()*point.y(),
                 this->cosAlpha()*point.y() + this->sinAlpha()*point.x(),
                 point.z()                          );
  }

  rotation3dz& invert(bool& success)
  {
    axisanglebase<T>::invert(success);
    return *this;
  }

  rotation3dz inverse(bool& success) const
  {
    rotation3dz inv(*this);
    inv.invert(success);
    return inv;
  }

};

// euler rotation about Z, Y', X".
template <typename T>
class rotation3dzyx {

 public:

  template <typename T1>
  rotation3dzyx(const rotation3dx<T1>& rot)
  :
  m_rot(detail::rotX(rot.cosAlpha(), rot.sinAlpha()))
  {
  }

  template <typename T1>
  rotation3dzyx(const rotation3dy<T1>& rot)
  :
  m_rot(detail::rotY(rot.cosAlpha(), rot.sinAlpha()))
  {
  }

  template <typename T1>
  rotation3dzyx(const rotation3dz<T1>& rot)
  :
  m_rot(detail::rotZ(rot.cosAlpha(), rot.sinAlpha()))
  {
  }

  rotation3dzyx(T phi, T theta, T psi)
  :
  m_rot(rotationX(psi)*rotationY(theta)*rotationZ(phi))
  {
  }

  rotation3dzyx() : m_rot(identity_matrix()) {}

  // construct from a 3x3 matrix
  explicit rotation3dzyx(const matrix<T, 3>& mat) : m_rot(mat) {}


  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation about X, Y', Z"
    return m_rot*point;
  }

  // equality comparison
  bool operator==(const rotation3dzyx& rhs) const {
    return (m_rot == rhs.m_rot);
  }

  // Invert this rotation3dzyx
  rotation3dzyx& invert(bool& success)
  {
    m_rot.invert(success);
    return *this;
  }
  // Return the inverse rotation3dzyx
  rotation3dzyx inverse(bool& success) const {
    return rotation3dzyx(*this).invert(success);
  }

  // element access
  const T& operator()(unsigned int i, unsigned int j) const
  {
    return m_rot(i,j);
  }
  // element access
  T& operator()(unsigned int i, unsigned int j)
  {
    return m_rot(i,j);
  }


 private:
  matrix<T, 3, 3> m_rot;
};

template <typename T>
class rotation3d {

 public:

  typedef T scalar_type;

  // default construction is identity transformation
  rotation3d() : m_rot(identity_matrix()) {}

  // Construct from a rotation about the X axis
  template <typename T1>
  rotation3d(const rotation3dx<T1>& rot)
  :
  m_rot(detail::rotX(rot.cosAlpha(), rot.sinAlpha())) {}

  // Construct from a rotation about the Y axis
  template <typename T1>
  rotation3d(const rotation3dy<T1>& rot)
  :
  m_rot(detail::rotY(rot.cosAlpha(), rot.sinAlpha())) {}

  // Construct from a rotation about the Z axis
  template <typename T1>
  rotation3d(const rotation3dz<T1>& rot)
  :
  m_rot(detail::rotZ(rot.cosAlpha(), rot.sinAlpha())) {}

  // Construct from a rotation about any axis
  template <typename T1>
  rotation3d(const axisangle<T1>& rot)
  :
  m_rot(detail::axisangle_(rot.axis(), rot.cosAlpha(), rot.sinAlpha())) {}

  // Construct from a rotation about the Z, Y' and X" axes
  template <typename T1>
  rotation3d(const rotation3dzyx<T1>& rot)
  {
    for (unsigned int r = 0; r < m_rot.rows(); ++r)
      for (unsigned int c = 0; c < m_rot.cols(); ++c)
        m_rot(r,c) = rot(r,c);
  }

  // construct from a 3x3 matrix
  template <typename T1>
  explicit rotation3d(const matrix<T1, 3>& mat) : m_rot(mat) {}

  // Invert this rotation3d
  rotation3d& invert(bool& success)
  {
    m_rot.invert(success);
    return *this;
  }
  // Return the inverse rotation3d
  rotation3d inverse(bool& success) const
  {
    rotation3d inv(*this);
    inv.invert(success);
    return inv;
  }
  // multiplication by another rotation3d
  rotation3d& operator*=(const rotation3d& rhs) {
    m_rot *= rhs.m_rot;
    return *this;
  }

  // multiplication by another rotation3d
  rotation3d operator*(const rotation3d& rhs) {
    rotation3d rot = rhs;
    rot.m_rot = m_rot*rhs.m_rot;
    return rot;
  }

  // multiplication by another rotation3dx
  template <typename T1>
  rotation3d operator*(const rotation3dx<T1>& rhs) {
    return (*this)*rotation3d(rhs);
  }
  // multiplication by another rotation3dy
  template <typename T1>
  rotation3d operator*(const rotation3dy<T1>& rhs) {
    return (*this)*rotation3d(rhs);
  }

 // multiplication by another rotation3dz
  template <typename T1>
  rotation3d operator*(const rotation3dz<T1>& rhs) {
    return (*this)*rotation3d(rhs);
  }

 // multiplication by another rotation3dz
  template <typename T1>
  rotation3d operator*(const rotation3dzyx<T1>& rhs) {
    return (*this)*rotation3d(rhs);
  }

  // equality comparison
  bool operator==(const rotation3d& rhs) const {
    return m_rot == rhs.m_rot;
  }

  /// apply a rotation to a point
  template <typename Point>
  Point operator*(const Point& point) const {
    return m_rot*point;
  }

  /// apply a rotation to a 3 row matrix
  template <typename T1, unsigned int C>
  matrix<T1,3,C> operator*(const matrix<T1,3,C>& mat) const {
    return m_rot*mat;
  }

  // equality comparison with tolerance
  bool equal(const rotation3d& rhs, int nEpsilons=1) const {
    return minimath::equal(m_rot, rhs.m_rot, nEpsilons);
  }
  // equality comparison with tolerance
  bool equal(const matrix<double,3,3>& mat, int nEpsilons=1) const {
    return minimath::equal(m_rot, mat, nEpsilons);
  }

  // element access
  const T& operator()(unsigned int i, unsigned int j) const
  {
    return m_rot(i,j);
  }
  // element access
  T& operator()(unsigned int i, unsigned int j)
  {
    return m_rot(i,j);
  }


 private:
  matrix<T, 3, 3> m_rot;
};

} // namespace minimath

#endif // MINIMATH_ROTATION3D_H_
