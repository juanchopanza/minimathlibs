//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimath.
// Subject to the BSD 2-Clause License
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MATH_ROTATION3D_H_
#define MATH_ROTATION3D_H_

#include "Math/Point3D.h"
#include "Math/Matrix.h"
#include "Math/MatrixOps.h"
#include "Math/Geom3DOps.h"
#include "Math/Utils.h"
#include <cmath>

namespace Math {

namespace detail
{

template <typename T>
inline Matrix<T,3,3> rotX(T cosA, T sinA)
{
  Matrix<T,3,3> rot = IdentityMatrix();
  rot(1,1) =  cosA;
  rot(2,2) =  cosA;
  rot(1,2) = -sinA;
  rot(2,1) =  sinA;
  return rot;

}

template <typename T>
inline Matrix<T,3,3> rotY(T cosA, T sinA)
{
  Matrix<T,3,3> rot = IdentityMatrix();
  rot(0,0) =  cosA;
  rot(2,2) =  cosA;
  rot(2,0) = -sinA;
  rot(0,2) =  sinA;
  return rot;
}

template <typename T>
inline Matrix<T,3,3> rotZ(T cosA, T sinA)
{
  Matrix<T,3,3> rot = IdentityMatrix();
  rot(0,0) =  cosA;
  rot(1,1) =  cosA;
  rot(0,1) = -sinA;
  rot(1,0) =  sinA;
  return rot;
}

template <typename T, typename V>
Matrix<T,3,3> axisAngle(V axis, T cosA, T sinA)
{
  T mag = std::sqrt(Math::mag2(axis));
  axis /= mag;

  Matrix<T,3,3> rot;

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
inline Matrix<T,3,3> rotationX(T alpha)
{
  const T c = std::cos(alpha);
  const T s = std::sin(alpha);
  return detail::rotX(c, s);
}

/// create a 3x3 matrix representing a rotation of alpha radians
/// about the Y axis
template <typename T>
inline Matrix<T,3,3> rotationY(T alpha)
{
  //Matrix<T,3,3> rot = IdentityMatrix();
  const T c = std::cos(alpha);
  const T s = std::sin(alpha);
  return detail::rotY(c, s);
}

/// create a 3x3 matrix representing a rotation of alpha radians
/// about the Z axis
template <typename T>
inline Matrix<T,3,3> rotationZ(T alpha)
{
  //Matrix<T,3,3> rot = IdentityMatrix();
  const T c = std::cos(alpha);
  const T s = std::sin(alpha);
  return detail::rotZ(c,s);
}

/// create a 3x3 matrix representing a rotation of alpha radians
/// about an axis
template <typename T, typename Axis>
Matrix<T,3,3> axisAngle(const Axis& axis, T alpha)
{
  //Matrix<T,3,3> rot = IdentityMatrix();
  const T c = std::cos(alpha);
  const T s = std::sin(alpha);
  return detail::axisAngle(axis, c, s);
}


template <typename T>
class AxisAngleBase {

 public:

  AxisAngleBase() : m_sin(0), m_cos(1) {}
  explicit AxisAngleBase(T angle)
  :
  m_sin(std::sin(angle)), m_cos(std::cos(angle)) {}

  T cosAlpha() const { return m_cos; };
  T sinAlpha() const { return m_sin; };

  bool operator==(const AxisAngleBase& rhs) const {
    return (compareWithTolerance(m_sin, rhs.sinAlpha(), T()) &&
            compareWithTolerance(m_cos, rhs.cosAlpha(), T()));
  }
  AxisAngleBase& invert(bool& success)
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
class AxisAngle : public AxisAngleBase<T> {

 public:

  typedef Point3D<T> axis_type;

 public:

  AxisAngle() : AxisAngleBase<T>(), m_axis(0,0,1) {}

  AxisAngle(const axis_type& axis) : AxisAngleBase<T>(), m_axis(axis) {}

  AxisAngle(T angle) : AxisAngleBase<T>(angle), m_axis() {}

  AxisAngle(const axis_type& axis, T angle)
  :
  AxisAngleBase<T>(angle),
  m_axis(axis)
  {
  }

  const axis_type& axis() const { return m_axis; }

  AxisAngle& invert(bool& success)
  {
    AxisAngleBase<T>::invert(success);
    return *this;
  }
  AxisAngle inverse(bool& success) const
  {
    AxisAngle inv(*this);
    inv.invert(success);
    return inv;
  }


 private:

  axis_type m_axis;

};

// rotation about the X axis
template <typename T>
class Rotation3DX  : public AxisAngleBase<T> {

 public:
  Rotation3DX() : AxisAngleBase<T>() {}
  explicit Rotation3DX(T angle) : AxisAngleBase<T>(angle) {}
  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation
    return Point(point.x(),
                 this->cosAlpha()*point.y() - this->sinAlpha()*point.z(),
                 this->cosAlpha()*point.z() + this->sinAlpha()*point.y() );
  }

  Rotation3DX& invert(bool& success)
  {
    AxisAngleBase<T>::invert(success);
    return *this;
  }
  Rotation3DX inverse(bool& success) const
  {
    Rotation3DX inv(*this);
    inv.invert(success);
    return inv;
  }

};

// rotation about the Y axis
template <typename T>
class Rotation3DY : public AxisAngleBase<T> {

 public:
  Rotation3DY() : AxisAngleBase<T>() {}
  explicit Rotation3DY(T angle) : AxisAngleBase<T>(angle) {}

  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation
    return Point(this->cosAlpha()*point.x() + this->sinAlpha()*point.z(),
                 point.y(),
                 this->cosAlpha()*point.z() - this->sinAlpha()*point.x() );
  }

  Rotation3DY& invert(bool& success)
  {
    AxisAngleBase<T>::invert(success);
    return *this;
  }

  Rotation3DY inverse(bool& success) const
  {
    Rotation3DY inv(*this);
    inv.invert(success);
    return inv;
  }

};

// rotation about the Z axis
template <typename T>
class Rotation3DZ : public AxisAngleBase<T> {

 public:
  Rotation3DZ() : AxisAngleBase<T>() {}
  explicit Rotation3DZ(T angle) : AxisAngleBase<T>(angle) {}

  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation
    return Point(this->cosAlpha()*point.x() - this->sinAlpha()*point.y(),
                 this->cosAlpha()*point.y() + this->sinAlpha()*point.x(),
                 point.z()                          );
  }

  Rotation3DZ& invert(bool& success)
  {
    AxisAngleBase<T>::invert(success);
    return *this;
  }

  Rotation3DZ inverse(bool& success) const
  {
    Rotation3DZ inv(*this);
    inv.invert(success);
    return inv;
  }

};

// euler rotation about Z, Y', X".
template <typename T>
class Rotation3DZYX {

 public:

  template <typename T1>
  Rotation3DZYX(const Rotation3DX<T1>& rot)
  :
  m_rot(detail::rotX(rot.cosAlpha(), rot.sinAlpha()))
  {
  }

  template <typename T1>
  Rotation3DZYX(const Rotation3DY<T1>& rot)
  :
  m_rot(detail::rotY(rot.cosAlpha(), rot.sinAlpha()))
  {
  }

  template <typename T1>
  Rotation3DZYX(const Rotation3DZ<T1>& rot)
  :
  m_rot(detail::rotZ(rot.cosAlpha(), rot.sinAlpha()))
  {
  }

  Rotation3DZYX(T phi, T theta, T psi)
  :
  m_rot(rotationX(psi)*rotationY(theta)*rotationZ(phi))
  {
  }

  Rotation3DZYX() : m_rot(IdentityMatrix()) {}

  // construct from a 3x3 matrix
  explicit Rotation3DZYX(const Matrix<T, 3>& mat) : m_rot(mat) {}


  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation about X, Y', Z"
    return m_rot*point;
  }

  // equality comparison
  bool operator==(const Rotation3DZYX& rhs) const {
    return (m_rot == rhs.m_rot);
  }

  // Invert this Rotation3DZYX
  Rotation3DZYX& invert(bool& success)
  {
    m_rot.invert(success);
    return *this;
  }
  // Return the inverse Rotation3DZYX
  Rotation3DZYX inverse(bool& success) const {
    return Rotation3DZYX(*this).invert(success);
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
  Matrix<T, 3, 3> m_rot;
};

template <typename T>
class Rotation3D {

 public:

  typedef T scalar_type;

  // default construction is identity transformation
  Rotation3D() : m_rot(IdentityMatrix()) {}

  // Construct from a rotation about the X axis
  template <typename T1>
  Rotation3D(const Rotation3DX<T1>& rot)
  :
  m_rot(detail::rotX(rot.cosAlpha(), rot.sinAlpha())) {}

  // Construct from a rotation about the Y axis
  template <typename T1>
  Rotation3D(const Rotation3DY<T1>& rot)
  :
  m_rot(detail::rotY(rot.cosAlpha(), rot.sinAlpha())) {}

  // Construct from a rotation about the Z axis
  template <typename T1>
  Rotation3D(const Rotation3DZ<T1>& rot)
  :
  m_rot(detail::rotZ(rot.cosAlpha(), rot.sinAlpha())) {}

  // Construct from a rotation about any axis
  template <typename T1>
  Rotation3D(const AxisAngle<T1>& rot)
  :
  m_rot(detail::axisAngle(rot.axis(), rot.cosAlpha(), rot.sinAlpha())) {}

  // Construct from a rotation about the Z, Y' and X" axes
  template <typename T1>
  Rotation3D(const Rotation3DZYX<T1>& rot)
  {
    for (unsigned int r = 0; r < m_rot.rows(); ++r)
      for (unsigned int c = 0; c < m_rot.cols(); ++c)
        m_rot(r,c) = rot(r,c);
  }

  // construct from a 3x3 matrix
  template <typename T1>
  explicit Rotation3D(const Matrix<T1, 3>& mat) : m_rot(mat) {}

  // Invert this Rotation3D
  Rotation3D& invert(bool& success)
  {
    m_rot.invert(success);
    return *this;
  }
  // Return the inverse Rotation3D
  Rotation3D inverse(bool& success) const
  {
    Rotation3D inv(*this);
    inv.invert(success);
    return inv;
  }
  // multiplication by another Rotation3D
  Rotation3D& operator*=(const Rotation3D& rhs) {
    m_rot *= rhs.m_rot;
    return *this;
  }

  // multiplication by another Rotation3D
  Rotation3D operator*(const Rotation3D& rhs) {
    Rotation3D rot = rhs;
    rot.m_rot = m_rot*rhs.m_rot;
    return rot;
  }

  // multiplication by another Rotation3DX
  template <typename T1>
  Rotation3D operator*(const Rotation3DX<T1>& rhs) {
    return (*this)*Rotation3D(rhs);
  }
  // multiplication by another Rotation3DY
  template <typename T1>
  Rotation3D operator*(const Rotation3DY<T1>& rhs) {
    return (*this)*Rotation3D(rhs);
  }

 // multiplication by another Rotation3DZ
  template <typename T1>
  Rotation3D operator*(const Rotation3DZ<T1>& rhs) {
    return (*this)*Rotation3D(rhs);
  }

 // multiplication by another Rotation3DZ
  template <typename T1>
  Rotation3D operator*(const Rotation3DZYX<T1>& rhs) {
    return (*this)*Rotation3D(rhs);
  }

  // equality comparison
  bool operator==(const Rotation3D& rhs) const {
    return m_rot == rhs.m_rot;
  }

  /// apply a rotation to a point
  template <typename Point>
  Point operator*(const Point& point) const {
    return m_rot*point;
  }

  /// apply a rotation to a 3 row matrix
  template <typename T1, unsigned int C>
  Matrix<T1,3,C> operator*(const Matrix<T1,3,C>& mat) const {
    return m_rot*mat;
  }

  // equality comparison with tolerance
  bool equal(const Rotation3D& rhs, int nEpsilons=1) const {
    return Math::equal(m_rot, rhs.m_rot, nEpsilons);
  }
  // equality comparison with tolerance
  bool equal(const Matrix<double,3,3>& mat, int nEpsilons=1) const {
    return Math::equal(m_rot, mat, nEpsilons);
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
  Matrix<T, 3, 3> m_rot;
};

} // namespace Math

#endif // MATH_ROTATION3D_H_
