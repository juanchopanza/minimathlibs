//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MATH_TRANSLATION3D_H_
#define MATH_TRANSLATION3D_H_

#include "Math/Point3D.h"
#include "Math/Matrix.h"

namespace Math {

template <typename T>
class Translation3D {

 public:

  typedef Point3D<T> vector_type;
  typedef typename vector_type::scalar_type scalar_type;

 public:

  Translation3D() {}

  template <typename Vector>
  explicit Translation3D(const Vector& v) : m_trans(v) {}
  Translation3D(T x, T y, T z) : m_trans(x,y,z) {}

  template <typename Point>
  Point operator*(const Point& point) const {
    return Point( point + m_trans );
  }

  template <typename T1>
  Translation3D operator*(const Translation3D<T1>& rhs) const {
    return Translation3D( m_trans + rhs.m_trans );
  }

  Translation3D inverse() const {
    return Translation3D( m_trans * -1 );
  }

  Translation3D& invert() {
    m_trans *= -1;
    return *this;
  }



  template <typename T1>
  bool operator==(const Translation3D<T1>& rhs) 
  {
    return m_trans == rhs.m_trans;
  }

  template <typename T1>
  bool operator!=(const Translation3D<T1>& rhs)
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
template <typename T1, typename T2>
Translation3D<T2> operator*(const Matrix<T1,3>& rot, 
                            const Translation3D<T2>&  point) 
{
  typedef typename Translation3D<T2>::vector_type vector_type_;
  T2 elements[3];
  for (unsigned int row = 0; row < 3; ++row) {
    T2 element = 0;
    for (unsigned int i = 0; i < 3; ++i) {
      element+= rot(row,i) * point[i];
    }
    elements[row] = element; // dot prod of LHS row, RHS col
  }
  return Translation3D<T2>(vector_type_(elements[0], elements[1], elements[2]));

} 


}

#endif // MATH_TRANSLATION3D_H_
