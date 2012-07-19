//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimath.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MATH_ROTATION3D_H__
#define MATH_ROTATION3D_H__

#include "Math/Point3D.h"
#include "Math/Matrix.h"
#include "Math/MatrixOps.h"
#include <cmath>

namespace Math {

namespace detail
{

inline Matrix<double,3,3> rotX(double cosA, double sinA)
{
  Matrix<double,3,3> rot = IdentityMatrix();
  rot(1,1) =  cosA;
  rot(2,2) =  cosA;
  rot(1,2) = -sinA;
  rot(2,1) =  sinA;
  return rot; 

}

inline Matrix<double,3,3> rotY(double cosA, double sinA)
{
  Matrix<double,3,3> rot = IdentityMatrix();
  rot(0,0) =  cosA;
  rot(2,2) =  cosA;
  rot(2,0) = -sinA;
  rot(0,2) =  sinA;
  return rot; 
}

inline Matrix<double,3,3> rotZ(double cosA, double sinA)
{
  Matrix<double,3,3> rot = IdentityMatrix();
  rot(0,0) =  cosA;
  rot(1,1) =  cosA;
  rot(0,1) = -sinA;
  rot(1,0) =  sinA;
  return rot;
}

template <typename V>
Matrix<double,3,3> axisAngle(V axis, double cosA, double sinA)
{
  double mag = std::sqrt(Math::mag2(axis));
  axis /= mag;

  Matrix<double,3,3> rot;

  const double cosComp = 1. - cosA;
  const double x = axis[0];
  const double y = axis[1];
  const double z = axis[2];

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
inline Matrix<double,3,3> rotationX(double alpha)
{
  const double c = std::cos(alpha);
  const double s = std::sin(alpha);
  return detail::rotX(c, s); 
}

/// create a 3x3 matrix representing a rotation of alpha radians
/// about the Y axis
inline Matrix<double,3,3> rotationY(double alpha)
{
  Matrix<double,3,3> rot = IdentityMatrix();
  const double c = std::cos(alpha);
  const double s = std::sin(alpha);
  return detail::rotY(c, s); 
}

/// create a 3x3 matrix representing a rotation of alpha radians
/// about the Z axis
inline Matrix<double,3,3> rotationZ(double alpha)
{
  Matrix<double,3,3> rot = IdentityMatrix();
  const double c = std::cos(alpha);
  const double s = std::sin(alpha);
  return detail::rotZ(c,s); 
}

/// create a 3x3 matrix representing a rotation of alpha radians
/// about an axis
template <typename Axis>
Matrix<double,3,3> axisAngle(const Axis& axis, double alpha)
{
  Matrix<double,3,3> rot = IdentityMatrix();
  const double c = std::cos(alpha);
  const double s = std::sin(alpha);
  return detail::axisAngle(axis, c, s); 
}


class AxisAngleBase {

 public:

  AxisAngleBase() : m_sin(0.), m_cos(1.) {}
  explicit AxisAngleBase(double angle) : m_sin(std::sin(angle)), m_cos(std::cos(angle)) {}

  double cosAlpha() const { return m_cos; };
  double sinAlpha() const { return m_sin; };

  bool operator==(const AxisAngleBase& rhs) const {
    return (m_sin == rhs.sinAlpha() && m_cos == rhs.cosAlpha());
  }
  AxisAngleBase& invert(bool& success)
  {
    m_sin *= -1;
    success = true;
    return *this;
  }
 private:
  double m_sin, m_cos;
};

/// Simple class representing a rotation about an
/// axis. 
class AxisAngle : public AxisAngleBase {

 public:

  typedef PointXYZD axis_type;

 public:

  AxisAngle() : AxisAngleBase(), m_axis(0,0,1) {}

  AxisAngle(const axis_type& axis) : AxisAngleBase(), m_axis(axis) {}

  AxisAngle(double angle) : AxisAngleBase(angle), m_axis() {}

  AxisAngle(const axis_type& axis, double angle) 
  :
  AxisAngleBase(angle), 
  m_axis(axis)
  {
  }

  const axis_type& axis() const { return m_axis; }

  AxisAngle& invert(bool& success)
  {
    AxisAngleBase::invert(success);
    return *this;
  }
  AxisAngle inverse(bool& success) const
  {
    return AxisAngle(*this).invert(success);
  }


 private:

  axis_type m_axis;

};

// rotation about the X axis
class Rotation3DX  : public AxisAngleBase {

 public:
  Rotation3DX() : AxisAngleBase() {}
  explicit Rotation3DX(double angle) : AxisAngleBase(angle) {}
  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation
    return Point(point.x(), 
                 cosAlpha()*point.y() - sinAlpha()*point.z(), 
                 cosAlpha()*point.z() + sinAlpha()*point.y() );
  }

  Rotation3DX& invert(bool& success)
  {
    AxisAngleBase::invert(success);
    return *this;
  }
  Rotation3DX inverse(bool& success) const
  {
    return Rotation3DX(*this).invert(success);
  }

};

// rotation about the Y axis
class Rotation3DY : public AxisAngleBase {

 public:
  Rotation3DY() : AxisAngleBase() {}
  explicit Rotation3DY(double angle) : AxisAngleBase(angle) {}

  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation
    return Point(cosAlpha()*point.x() + sinAlpha()*point.z(), 
                 point.y(), 
                 cosAlpha()*point.z() - sinAlpha()*point.x() );
  }

  Rotation3DY& invert(bool& success)
  {
    AxisAngleBase::invert(success);
    return *this;
  }
  Rotation3DY inverse(bool& success) const
  {
    return Rotation3DY(*this).invert(success);
  }

};

// rotation about the Z axis
class Rotation3DZ : public AxisAngleBase {

 public:
  Rotation3DZ() : AxisAngleBase() {}
  explicit Rotation3DZ(double angle) : AxisAngleBase(angle) {}

  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation
    return Point(cosAlpha()*point.x() - sinAlpha()*point.y(), 
                 cosAlpha()*point.y() + sinAlpha()*point.x(), 
                 point.z()                          );
  }

  Rotation3DZ& invert(bool& success)
  {
    AxisAngleBase::invert(success);
    return *this;
  }
  Rotation3DZ inverse(bool& success) const
  {
    return Rotation3DZ(*this).invert(success);
  }

};

// euler rotation about Z, Y', X".
class Rotation3DZYX {

 public:

  Rotation3DZYX(const Rotation3DX& rot) 
  : 
  m_rot(detail::rotX(rot.cosAlpha(), rot.sinAlpha()))
  {
  }

  Rotation3DZYX(const Rotation3DY& rot)  
  : 
  m_rot(detail::rotY(rot.cosAlpha(), rot.sinAlpha()))
  {
  }

  Rotation3DZYX(const Rotation3DZ& rot)
  : 
  m_rot(detail::rotZ(rot.cosAlpha(), rot.sinAlpha()))
  {
  }

  Rotation3DZYX(double phi, double theta, double psi) 
  : 
  m_rot(rotationX(psi)*rotationY(theta)*rotationZ(phi))
  {
  }

  Rotation3DZYX() : m_rot(IdentityMatrix()) {}

  // construct from a 3x3 matrix
  explicit Rotation3DZYX(const Matrix<double, 3>& mat) : m_rot(mat) {}


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
  const double& operator()(unsigned int i, unsigned int j) const
  {
    return m_rot(i,j);
  }
  // element access
  double& operator()(unsigned int i, unsigned int j)
  {
    return m_rot(i,j);
  }


 private:
  Matrix<double, 3, 3> m_rot;
};

class Rotation3D {

 public:

  typedef double scalar_type;

  // default construction is identity transformation
  Rotation3D() : m_rot(IdentityMatrix()) {}

  // Construct from a rotation about the X axis
  Rotation3D(const Rotation3DX& rot)
  :
  m_rot(detail::rotX(rot.cosAlpha(), rot.sinAlpha())) {}

  // Construct from a rotation about the Y axis
  Rotation3D(const Rotation3DY& rot)
  :
  m_rot(detail::rotY(rot.cosAlpha(), rot.sinAlpha())) {}

  // Construct from a rotation about the Z axis
  Rotation3D(const Rotation3DZ& rot)
  :
  m_rot(detail::rotZ(rot.cosAlpha(), rot.sinAlpha())) {}

  // Construct from a rotation about any axis
  Rotation3D(const AxisAngle& rot)
  :
  m_rot(detail::axisAngle(rot.axis(), rot.cosAlpha(), rot.sinAlpha())) {}

  // Construct from a rotation about the Z, Y' and X" axes
  Rotation3D(const Rotation3DZYX& rot)
  {
    for (unsigned int r = 0; r < m_rot.rows(); ++r)
      for (unsigned int c = 0; c < m_rot.cols(); ++c)
        m_rot(r,c) = rot(r,c);
  }

  // construct from a 3x3 matrix
  explicit Rotation3D(const Matrix<double, 3>& mat) : m_rot(mat) {}

  // Invert this Rotation3D
  Rotation3D& invert(bool& success)
  {
    m_rot.invert(success);
    return *this;
  }
  // Return the inverse Rotation3D
  Rotation3D inverse(bool& success) const {
    return Rotation3D(*this).invert(success);
  }
  // multiplication by another Rotation3D
  Rotation3D& operator*=(const Rotation3D& rhs) {
    m_rot *= rhs.m_rot;
    return *this;
  }

  // multiplication by another Rotation3D
  Rotation3D operator*(Rotation3D rhs) {
    rhs.m_rot = m_rot*rhs.m_rot;
    return rhs;
  }

  // multiplication by another Rotation3DX
  Rotation3D operator*(const Rotation3DX& rhs) {
    return (*this)*Rotation3D(rhs);
  }
  // multiplication by another Rotation3DY
  Rotation3D operator*(const Rotation3DY& rhs) {
    return (*this)*Rotation3D(rhs);
  }

 // multiplication by another Rotation3DZ
  Rotation3D operator*(const Rotation3DZ& rhs) {
    return (*this)*Rotation3D(rhs);
  }

 // multiplication by another Rotation3DZ
  Rotation3D operator*(const Rotation3DZYX& rhs) {
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
  template <typename T, unsigned int C>
  Matrix<T,3,C> operator*(const Matrix<T,3,C>& mat) const {
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
  const double& operator()(unsigned int i, unsigned int j) const
  {
    return m_rot(i,j);
  }
  // element access
  double& operator()(unsigned int i, unsigned int j)
  {
    return m_rot(i,j);
  }


 private:
  Matrix<double, 3, 3> m_rot;
};

} // namespace Math

#endif // MATH_ROTATION3D_H__
