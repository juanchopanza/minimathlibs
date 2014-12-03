//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MATH_TRANSFORM3D_H_
#define MATH_TRANSFORM3D_H_

#include "minimath/rotation3d.hpp"
#include "minimath/translation3d.hpp"
#include "minimath/point3d.hpp"

namespace minimath {

template <typename T>
class transform3d {

 public:
  transform3d()
  : 
  m_mat(identity_matrix())
  {}

  template <typename T1>
  transform3d(const rotation3d<T1>& rot) 
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
  transform3d(const translation3d<T1>& trans) 
  :
  m_mat(identity_matrix()) 
  {
    for (unsigned int r = 0; r < 3; ++r)
    {
      m_mat(r,3) = trans[r];
    }
  }

  /// Construct from a rotation and a translation.
  template <typename T1, typename T2>
  transform3d(const rotation3d<T1>& rot, const translation3d<T2> trans) 
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
  transform3d(const translation3d<T1>& trans, const rotation3d<T2>& rot) 
  :
  m_mat() 
  {
    translation3d<T> trans_ = rot*trans; 
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
  explicit transform3d(const matrix<T1, 3, 4>& mat) : m_mat(mat) {}

  /// Apply the transformation to a 3D point
  template <typename Point>
  Point operator*(const Point& point) const {
    return (m_mat*point);
  }

  /// Product of two transformations 
  template <typename T1>
  transform3d operator*(const transform3d<T1>& rhs) const 
  {
    matrix<T,3,4> mat;
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

    return transform3d(mat);
  }

  /// Apply trnasformation to a 4xN matrix
  template <typename T1, unsigned int N>
  matrix<T,3,N> operator*(const matrix<T1,4,N>& rhs)
  {
    return m_mat*rhs;
  }

  transform3d& invert(bool& success)
  {
    // we need Tr^-1 * R`-1
    transform3d tmp(translation().inverse(), rotation().inverse(success));
    if (success)
    {
      m_mat = tmp.m_mat;
    }
    return *this;
  }

  transform3d inverse(bool& success) const
  {
    return transform3d(*this).invert(success);
  }

  /// return the underlying 3D rotation
  rotation3d<T> rotation() const 
  {
    rotation3d<T> tmp;
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
  translation3d<T> translation() const
  {
    return translation3d<T>(pointxyzd(m_mat(0,3), m_mat(1,3), m_mat(2,3)));
  }

  std::ostream& print(std::ostream& out) const
  {
    return out << m_mat;
  }

 private:
  matrix<T,3,4> m_mat;

};

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const transform3d<T>& t)
{
  out << "minimath::transform3d\n";
  return t.print(out) << "\n";
}

}

#endif // MATH_TRANSFORM3D_H_
