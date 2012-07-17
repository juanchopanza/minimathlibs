//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MATH_TRANSLATION3D_H__
#define MATH_TRANSLATION3D_H__

#include "Math/Point3D.h"
#include "Math/Matrix.h"

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

  Translation3D inverse() const {
    return Translation3D( m_trans * -1 );
  }

  Translation3D& invert() {
    m_trans *= -1;
    return *this;
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

// some useful operations

/// multiplication between a 3x3 matrix and a 3D translation 
template <typename T>
Translation3D operator*(const Matrix<T,3>& rot, 
                        const Translation3D&  point) 
{
  typedef Translation3D::vector_type vector_type_;
  double elements[3];
  for (unsigned int row = 0; row < 3; ++row) {
    double element = 0;
    for (unsigned int i = 0; i < 3; ++i) {
      element+= rot(row,i) * point[i];
    }
    elements[row] = element; // dot prod of LHS row, RHS col
  }
  return Translation3D(vector_type_(elements[0], elements[1], elements[2]));

} 


}

#endif // MATH_TRANSLATION3D_H__
