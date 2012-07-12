//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//


#ifndef MATH_POINT3D_H__
#define MATH_POINT3D_H__

#include <cmath>
#include <ostream>
#include <limits>
#include "Math/CoordSystem3D.h"
#include "Math/Point3DOps.h"

namespace Math {

template <typename T, template <typename> class CoordSystem>
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
    return equalXYZ(*this, rhs);
  }

  // inequality operator
  template <typename Point>
  bool operator!=(const Point& rhs) const {
    return !equalXYZ(*this, rhs);
  }


  // increment
  template <typename Coords>
  Point3D& operator += (const Coords& rhs) {
    m_coords.x() += rhs.x();
    m_coords.y() += rhs.y();
    m_coords.z() += rhs.z();
    return *this;
  }

  // decrement
  template <typename Coords>
  Point3D& operator -= (const Coords& rhs) {
    m_coords.x() -= rhs.x();
    m_coords.y() -= rhs.y();
    m_coords.z() -= rhs.z();
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
    m_coords.x() *= rhs;
    m_coords.y() *= rhs;
    m_coords.z() *= rhs;
    return *this;
  }

  template <typename Scalar>
  Point3D& operator /= (Scalar rhs) {
    m_coords.x() /= rhs;
    m_coords.y() /= rhs;
    m_coords.z() /= rhs;
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



typedef Point3D<double, CoordSystemXYZ> PointXYZD;
typedef Point3D<float, CoordSystemXYZ> PointXYZF;

} // namespace Math

#endif // MATH_POINT3D_H__
