//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
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
  explicit Transform3D(const Rotation3D& rot) : m_rot(rot), m_trans() {}
  explicit Transform3D(const Translation3D& trans) : m_rot(), m_trans(trans) {}
  Transform3D(const Rotation3D& rot, const Translation3D trans) : m_rot(rot), m_trans(trans) {}
  Transform3D(const Translation3D& trans, const Rotation3D& rot) : m_rot(rot), m_trans(rot*trans) {}
  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a rotation and translation
    return m_trans*(m_rot*point);
    //return (m_trans*point);
  }

 private:
  Rotation3D m_rot;
  Translation3D m_trans;

};

}

#endif // MATH_TRANSFORM3D_H__
