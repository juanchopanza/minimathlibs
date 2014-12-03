//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.

// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MINIMATH_TRANSLATION3D_H_
#define MINIMATH_TRANSLATION3D_H_

#include "minimath/point3d.hpp"
#include "minimath/matrix.hpp"

namespace minimath {

template <typename T>
class translation3d {

 public:

  typedef point3d<T> vector_type;
  typedef typename vector_type::scalar_type scalar_type;

 public:

  translation3d() {}

  template <typename Vector>
  explicit translation3d(const Vector& v) : m_trans(v) {}
  translation3d(T x, T y, T z) : m_trans(x,y,z) {}

  template <typename Point>
  Point operator*(const Point& point) const {
    return Point( point + m_trans );
  }

  template <typename T1>
  translation3d operator*(const translation3d<T1>& rhs) const {
    return translation3d( m_trans + rhs.m_trans );
  }

  translation3d inverse() const {
    return translation3d( m_trans * -1 );
  }

  translation3d& invert() {
    m_trans *= -1;
    return *this;
  }



  template <typename T1>
  bool operator==(const translation3d<T1>& rhs) 
  {
    return m_trans == rhs.m_trans;
  }

  template <typename T1>
  bool operator!=(const translation3d<T1>& rhs)
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
translation3d<T2> operator*(const matrix<T1,3>& rot, 
                            const translation3d<T2>&  point) 
{
  typedef typename translation3d<T2>::vector_type vector_type_;
  T2 elements[3];
  for (unsigned int row = 0; row < 3; ++row) {
    T2 element = 0;
    for (unsigned int i = 0; i < 3; ++i) {
      element+= rot(row,i) * point[i];
    }
    elements[row] = element; // dot prod of LHS row, RHS col
  }
  return translation3d<T2>(vector_type_(elements[0], elements[1], elements[2]));

} 


}

#endif // MINIMATH_TRANSLATION3D_H_
