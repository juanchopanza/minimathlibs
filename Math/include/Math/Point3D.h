//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MATH_POINT3D_H_
#define MATH_POINT3D_H_

#include <cmath>
#include <ostream>
#include <limits>
#include "Math/type_traits.hpp"
#include "Math/CoordSystem3D.h"
#include "Math/Point3DOps.h"

namespace Math {

template <typename T, template <typename> class CoordSystem=CoordSystemXYZ>
class Point3D {

 public :

  typedef T scalar_type;
  typedef T value_type;

  Point3D() : m_coords() {} 
  Point3D(T x, T y, T z) : m_coords(x,y,z) {} 

  template <typename P>
  Point3D(const P& rhs) : m_coords(rhs.x(), rhs.y(), rhs.z())  {} 

  // cartesian coordinate system
  T x() const { return m_coords.x();}
  T y() const { return m_coords.y();}
  T z() const { return m_coords.z();}

  Point3D& x(const value_type& x) 
  { 
    m_coords.x(x);
    return *this;
  }

  Point3D& y(const value_type& y) 
  { 
    m_coords.y(y);
    return *this;
  }
  Point3D& z(const value_type& z) 
  { 
    m_coords.z(z);
    return *this;
  }

  // cylindrical coordinate system
  // to-do: implement
  T r() const { return m_coords.r();}
  T phi() const { return m_coords.phi();}

  // spherical coordinate system
  // to-do: implement
  T rSpherical() const { m_coords.rSpherical();}
  T phiSpherical() const { return m_coords.phi();}
  T psi() const { return m_coords.psi();}

  // equality operator
  template <typename Point>
  bool operator==(const Point& rhs) const {
    return equal(*this, rhs, 1);
  }

  // inequality operator
  template <typename Point>
  bool operator!=(const Point& rhs) const {
    return !equal(*this, rhs, 1);
  }


  // increment
  template <typename Coords>
  Point3D& operator += (const Coords& rhs) {
    m_coords += rhs;
    return *this;
  }

  // decrement
  template <typename Coords>
  Point3D& operator -= (const Coords& rhs) {
    m_coords -= rhs;
    return *this;
  }

  template <typename Coords>
  Point3D operator+(const Coords& rhs) const {
    return Point3D(x()+rhs.x(), y()+rhs.y(), z()+rhs.z());
  }

  template <typename Coords>
  Point3D operator-(const Coords& rhs) const {
    return Point3D(x()-rhs.x(), y()-rhs.y(), z()-rhs.z());
  }


  template <typename Scalar>
  Point3D& operator *= (Scalar rhs) {
    m_coords *= rhs;
    return *this;
  }

  template <typename Scalar>
  Point3D& operator /= (Scalar rhs) {
    m_coords /= rhs;
    return *this;
  }

  // access to underlying data
  T& operator[](unsigned int i) {return m_coords[i];}
  const T& operator[](unsigned int i) const {return m_coords[i];}

 private:
  CoordSystem<T> m_coords;

};

template <typename T, template<typename> class CoordSystem>
std::ostream& operator << (std::ostream& out, const Point3D<T, CoordSystem>& point)
{
  return out << "Point3D XYZ( " << point.x() << ", " << point.y() << ", " << point.z() << ")";
}

// addition with foreign vector
template <typename P, typename T, template <typename> class C>
typename enable_if<is_point3d<P>::value, Point3D<T,C> >::type
operator+(const P& lhs, const Point3D<T, C>&  rhs)
{
  return Point3D<T,C>(lhs.x()+rhs.x(), lhs.y()+rhs.y(), lhs.z()+rhs.z());
}


// scalar multiplication
template <typename T, template <typename> class C>
Point3D<T, C> operator*(const Point3D<T, C>&  point,
                        const typename Point3D<T,C>::scalar_type& scalar)
{
  return Point3D<T,C>(point) *= typename Point3D<T,C>::scalar_type(scalar);
}

// scalar multiplication
template <typename T, template <typename> class C>
Point3D<T, C> operator*(const typename Point3D<T,C>::scalar_type& scalar,
                        const Point3D<T, C>&  point)
{
  return Point3D<T,C>(point) *= typename Point3D<T,C>::scalar_type(scalar);
}

// scalar division: only allow Point on RHS
template <typename T, template <typename> class C>
Point3D<T, C> operator/(const Point3D<T, C>&  point,
                        const typename Point3D<T,C>::scalar_type& scalar)
{
  return Point3D<T,C>(point) /= typename Point3D<T,C>::scalar_type(scalar);
}

typedef Point3D<double, CoordSystemXYZ> PointXYZD;
typedef Point3D<float, CoordSystemXYZ> PointXYZF;

} // namespace Math

#endif // MATH_POINT3D_H_
