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

  typedef PointXYZD vector_type;
  typedef vector_type::scalar_type scalar_type;

 public:

  Translation3D() {}

  template <typename Vector>
  explicit Translation3D(const Vector& v) : m_trans(v) {}
  Translation3D(double x, double y, double z) : m_trans(x,y,z) {}

  template <typename Point>
  Point operator*(const Point& point) const {
    return Point( point + m_trans );
  }

  Translation3D operator*(const Translation3D& rhs) const {
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

  // access to underlying data
  scalar_type& operator[](unsigned int i) {return m_trans[i];}

  const scalar_type& operator[](unsigned int i) const {return m_trans[i];}

 private:

  vector_type m_trans;
};

}

#endif // MATH_TRANSLATION3D_H__
