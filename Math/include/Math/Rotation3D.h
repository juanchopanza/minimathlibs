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

class AxisAngle3DBase {

 public:

  AxisAngle3DBase() : m_sin(0.), m_cos(1.) {}
  explicit AxisAngle3DBase(double angle) : m_sin(std::sin(angle)), m_cos(std::cos(angle)) {}

  double cosAlpha() const { return m_cos; };
  double sinAlpha() const { return m_sin; };

  bool operator==(const AxisAngle3DBase& rhs) const {
    return (m_sin == rhs.sinAlpha() && m_cos == rhs.cosAlpha());
  }
  AxisAngle3DBase& invert(bool& success)
  {
    m_sin *= -1;
    success = true;
    return *this;
  }
 private:
  double m_sin, m_cos;
};

// rotation about the X axis
class Rotation3DX  : public AxisAngle3DBase {

 public:
  Rotation3DX() : AxisAngle3DBase() {}
  explicit Rotation3DX(double angle) : AxisAngle3DBase(angle) {}
  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation
    return Point(point.x(), 
                 cosAlpha()*point.y() - sinAlpha()*point.z(), 
                 cosAlpha()*point.z() + sinAlpha()*point.y() );
  }

  Rotation3DX& invert(bool& success)
  {
    AxisAngle3DBase::invert(success);
    return *this;
  }
  Rotation3DX inverse(bool& success) const
  {
    return Rotation3DX(*this).invert(success);
  }

};

// rotation about the Y axis
class Rotation3DY : public AxisAngle3DBase {

 public:
  Rotation3DY() : AxisAngle3DBase() {}
  explicit Rotation3DY(double angle) : AxisAngle3DBase(angle) {}

  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation
    return Point(cosAlpha()*point.x() + sinAlpha()*point.z(), 
                 point.y(), 
                 cosAlpha()*point.z() - sinAlpha()*point.x() );
  }

  Rotation3DY& invert(bool& success)
  {
    AxisAngle3DBase::invert(success);
    return *this;
  }
  Rotation3DY inverse(bool& success) const
  {
    return Rotation3DY(*this).invert(success);
  }

};

// rotation about the Z axis
class Rotation3DZ : public AxisAngle3DBase {

 public:
  Rotation3DZ() : AxisAngle3DBase() {}
  explicit Rotation3DZ(double angle) : AxisAngle3DBase(angle) {}

  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation
    return Point(cosAlpha()*point.x() - sinAlpha()*point.y(), 
                 cosAlpha()*point.y() + sinAlpha()*point.x(), 
                 point.z()                          );
  }

  Rotation3DZ& invert(bool& success)
  {
    AxisAngle3DBase::invert(success);
    return *this;
  }
  Rotation3DZ inverse(bool& success) const
  {
    return Rotation3DZ(*this).invert(success);
  }

};

// euler rotation about Y, Y', X".
// should we replace implementation by a matrix?
class Rotation3DZYX {

 public:

  Rotation3DZYX(const Rotation3DX& rot) : m_rotX(rot) {}
  Rotation3DZYX(const Rotation3DY& rot) : m_rotY(rot) {}
  Rotation3DZYX(const Rotation3DZ& rot) : m_rotZ(rot) {}
  Rotation3DZYX(double phi, double theta, double psi) : m_rotZ(phi), m_rotY(theta), m_rotX(psi) {}
  Rotation3DZYX() {}
  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation about X, Y', Z"
    return m_rotX*(m_rotY*(m_rotZ*point));
  }

  // equality comparison
  bool operator==(const Rotation3DZYX& rhs) const {
    return (m_rotZ == rhs.m_rotZ) && 
           (m_rotY == rhs.m_rotY) && 
           (m_rotX == rhs.m_rotX);
  }


 private:
  Rotation3DZ m_rotZ;
  Rotation3DY m_rotY;
  Rotation3DX m_rotX;
};

class Rotation3D {

 public:

  typedef double scalar_type;

  // default construction is identity transformation
  Rotation3D() : m_rot(IdentityMatrix()) {}

  // Construct from a rotation about the X axis
  Rotation3D(const Rotation3DX& rot) : m_rot(IdentityMatrix()) 
  {
    const double cosA = rot.cosAlpha();
    const double sinA = rot.sinAlpha();
    m_rot(1,1) =  cosA;
    m_rot(2,2) =  cosA;
    m_rot(1,2) = -sinA;
    m_rot(2,1) =  sinA;
  }

  // Construct from a rotation about the Y axis
  Rotation3D(const Rotation3DY& rot) : m_rot(IdentityMatrix())
  {
    const double cosA = rot.cosAlpha();
    const double sinA = rot.sinAlpha();
    m_rot(0,0) =  cosA;
    m_rot(2,2) =  cosA;
    m_rot(2,0) = -sinA;
    m_rot(0,2) =  sinA;
  }

  // Construct from a rotation about the Z axis
  Rotation3D(const Rotation3DZ& rot) : m_rot(IdentityMatrix())
  {
    const double cosA = rot.cosAlpha();
    const double sinA = rot.sinAlpha();
    m_rot(0,0) =  cosA;
    m_rot(1,1) =  cosA;
    m_rot(0,1) = -sinA;
    m_rot(1,0) =  sinA;
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

 private:
  Matrix<double, 3, 3> m_rot;
};


}

#endif // MATH_ROTATION3D_H__
