//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MATH_TRANSFORM3D_H__
#define MATH_TRANSFORM3D_H__

#include "Math/Rotation3D.h"
#include "Math/Translation3D.h"
#include "Math/Point3D.h"

namespace Math {

template <typename T>
class Transform3D {

 public:
  Transform3D()
  : 
  m_mat(IdentityMatrix())
  {}

  template <typename T1>
  Transform3D(const Rotation3D<T1>& rot) 
  : 
  m_mat()
  {
    for (unsigned int r = 0; r < 3; ++r)
    {
      for (unsigned int c = 0; c < 3; ++c)
      {
        m_mat(r,c) = rot(r,c);
      }
    }
  }

  template <typename T1>
  Transform3D(const Translation3D<T1>& trans) 
  :
  m_mat(IdentityMatrix()) 
  {
    for (unsigned int r = 0; r < 3; ++r)
    {
      m_mat(r,3) = trans[r];
    }
  }

  /// Construct from a rotation and a translation.
  template <typename T1, typename T2>
  Transform3D(const Rotation3D<T1>& rot, const Translation3D<T2> trans) 
  :
  m_mat() 
  {
    for (unsigned int r = 0; r < 3; ++r)
    {
      for (unsigned int c = 0; c < 3; ++c)
      {
        m_mat(r,c) = rot(r,c);
      }
      m_mat(r,3) = trans[r];
    }

  }

  ///
  /// Construct the equivalent of a translation followed by a rotation.
  /// Internally converted to a rotation followed by a translation.
  ///
  template <typename T1, typename T2>
  Transform3D(const Translation3D<T1>& trans, const Rotation3D<T2>& rot) 
  :
  m_mat() 
  {
    Translation3D<T> trans_ = rot*trans; 
    for (unsigned int r = 0; r < 3; ++r)
    {
      for (unsigned int c = 0; c < 3; ++c)
      {
        m_mat(r,c) = rot(r,c);
      }
      m_mat(r,3) = trans_[r];
    }
  }

  /// Construct from a 3x4 matrix
  template <typename T1>
  explicit Transform3D(const Matrix<T1, 3, 4>& mat) : m_mat(mat) {}

  /// Apply the transformation to a 3D point
  template <typename Point>
  Point operator*(const Point& point) const {
    return (m_mat*point);
  }

  /// Product of two transformations 
  template <typename T1>
  Transform3D operator*(const Transform3D<T1>& rhs) const 
  {
    Matrix<T,3,4> mat;
    mat(0,0) =  m_mat(0,0)*rhs.m_mat(0,0) + m_mat(0,1)*rhs.m_mat(1,0) + m_mat(0,2)*rhs.m_mat(2,0);
    mat(0,1) =  m_mat(0,0)*rhs.m_mat(0,1) + m_mat(0,1)*rhs.m_mat(1,1) + m_mat(0,2)*rhs.m_mat(2,1);
    mat(0,2) =  m_mat(0,0)*rhs.m_mat(0,2) + m_mat(0,1)*rhs.m_mat(1,2) + m_mat(0,2)*rhs.m_mat(2,2);
    mat(0,3) =  m_mat(0,0)*rhs.m_mat(0,3) + m_mat(0,1)*rhs.m_mat(1,3) + m_mat(0,2)*rhs.m_mat(2,3) + m_mat(0,3);
   
    mat(1,0) =  m_mat(1,0)*rhs.m_mat(0,0) + m_mat(1,1)*rhs.m_mat(1,0) + m_mat(1,2)*rhs.m_mat(2,0);
    mat(1,1) =  m_mat(1,0)*rhs.m_mat(0,1) + m_mat(1,1)*rhs.m_mat(1,1) + m_mat(1,2)*rhs.m_mat(2,1);
    mat(1,2) =  m_mat(1,0)*rhs.m_mat(0,2) + m_mat(1,1)*rhs.m_mat(1,2) + m_mat(1,2)*rhs.m_mat(2,2);
    mat(1,3) =  m_mat(1,0)*rhs.m_mat(0,3) + m_mat(1,1)*rhs.m_mat(1,3) + m_mat(1,2)*rhs.m_mat(2,3) + m_mat(1,3);
                   
    mat(2,0) =  m_mat(2,0)*rhs.m_mat(0,0) + m_mat(2,1)*rhs.m_mat(1,0) + m_mat(2,2)*rhs.m_mat(2,0);
    mat(2,1) =  m_mat(2,0)*rhs.m_mat(0,1) + m_mat(2,1)*rhs.m_mat(1,1) + m_mat(2,2)*rhs.m_mat(2,1);
    mat(2,2) =  m_mat(2,0)*rhs.m_mat(0,2) + m_mat(2,1)*rhs.m_mat(1,2) + m_mat(2,2)*rhs.m_mat(2,2);
    mat(2,3) =  m_mat(2,0)*rhs.m_mat(0,3) + m_mat(2,1)*rhs.m_mat(1,3) + m_mat(2,2)*rhs.m_mat(2,3) + m_mat(2,3);

    return Transform3D(mat);
  }

  /// Apply trnasformation to a 4xN matrix
  template <typename T1, unsigned int N>
  Matrix<T,3,N> operator*(const Matrix<T1,4,N>& rhs)
  {
    return m_mat*rhs;
  }

  Transform3D& invert(bool& success)
  {
    // we need Tr^-1 * R`-1
    Transform3D tmp(translation().inverse(), rotation().inverse(success));
    if (success)
    {
      m_mat = tmp.m_mat;
    }
    return *this;
  }

  Transform3D inverse(bool& success) const
  {
    return Transform3D(*this).invert(success);
  }

  /// return the underlying 3D rotation
  Rotation3D<T> rotation() const 
  {
    Rotation3D<T> tmp;
    for (unsigned int r = 0; r < 3; ++r)
    {
      for (unsigned int c = 0; c < 3; ++c)
      {
        tmp(r,c) = m_mat(r,c);
      }
    }
    return tmp;
  }

  /// return the underlying 3D translation
  Translation3D<T> translation() const
  {
    return Translation3D<T>(PointXYZD(m_mat(0,3), m_mat(1,3), m_mat(2,3)));
  }

  std::ostream& print(std::ostream& out) const
  {
    return out << m_mat;
  }

 private:
  Matrix<T,3,4> m_mat;

};

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Transform3D<T>& t)
{
  out << "Math::Transform3D\n";
  return t.print(out) << "\n";
}

}

#endif // MATH_TRANSFORM3D_H__
