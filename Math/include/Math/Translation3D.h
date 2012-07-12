//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//


#ifndef MATH_TRANSLATION3D_H__
#define MATH_TRANSLATION3D_H__

#include "Math/Point3D.h"

namespace Math {

class Translation3D {

 public:
  Translation3D() {}
  template <typename Vector>
  explicit Translation3D(const Vector& v) : m_trans(v) {}
  Translation3D(double x, double y, double z) : m_trans(x,y,z) {}
  template <typename Point>
  Point operator*(const Point& point) const {
    // apply a translation
    return Point( point + m_trans );
  }
  Translation3D operator*(const Translation3D& rhs) const {
    // apply a translation
    return Translation3D( m_trans + rhs.m_trans );
  }


  bool operator==(const Translation3D& rhs) 
  {
    return m_trans == rhs.m_trans;
  }
  bool operator!=(const Translation3D& rhs)
  {
    return !operator==(rhs);
  }

 private:
  PointXYZD m_trans;
};

}

#endif // MATH_TRANSLATION3D_H__
