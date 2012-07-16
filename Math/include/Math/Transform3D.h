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

class Transform3D {

 public:
  Transform3D() {}
  explicit Transform3D(const Rotation3D& rot) 
  : 
  m_mat()
  //m_rot(rot), 
  //m_trans() 
  {
    for (unsigned int r = 0; r < 3; ++r)
    {
      for (unsigned int c = 0; c < 3; ++c)
      {
        m_mat(r,c) = rot(r,c);
      }
    }
  }

  explicit Transform3D(const Translation3D& trans) 
  :
  m_mat(IdentityMatrix()) 
  //m_rot(), 
  //m_trans(trans) 
  {
    for (unsigned int r = 0; r < 3; ++r)
    {
      m_mat(r,3) = trans[r];
    }
  }

  Transform3D(const Rotation3D& rot, const Translation3D trans) 
  :
  m_mat() 
  //m_rot(rot), 
  //m_trans(trans)
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

  Transform3D(const Translation3D& trans, const Rotation3D& rot) 
  :
  m_mat() 
  //m_rot(rot), 
  //m_trans(rot*trans) 
  {
    Translation3D trans_ = rot*trans; 
    for (unsigned int r = 0; r < 3; ++r)
    {
      for (unsigned int c = 0; c < 3; ++c)
      {
        m_mat(r,c) = rot(r,c);
      }
      m_mat(r,3) = trans_[r];
    }
  }

  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation and translation
    //return m_trans*(m_rot*point);
    return (m_mat*point);
  }

  Transform3D& invert(bool& success)
  {
    //m_rot.invert(success);
    //m_trans.invert();
    //m_trans = m_rot*m_trans;
    success = false;
    return *this;
  }

  Transform3D inverse(bool& success) const
  {
    return Transform3D(*this).invert(success);
  }

 private:
  Matrix<double,3,4> m_mat;
  //Rotation3D m_rot;
  //Translation3D m_trans;

};

}

#endif // MATH_TRANSFORM3D_H__
