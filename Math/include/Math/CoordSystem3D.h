//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//



#ifndef MATH_COORDSYSTEM3D_H__
#define MATH_COORDSYSTEM3D_H__

#include <ostream>
#include "Math/Point3DOps.h"

namespace Math {

template <typename T>
class CoordSystemXYZ {

 public:

  typedef T scalar_type;
  typedef T value_type;

  CoordSystemXYZ() : m_data() {}
  CoordSystemXYZ(T x, T y, T z)  {
    m_data[0]=x;
    m_data[1]=y;
    m_data[2]=z;
  }

  // cartesian coordinate system
  const T& x() const { return m_data[0];}
  const T& y() const { return m_data[1];}
  const T& z() const { return m_data[2];}
  T& x() { return m_data[0];}
  T& y() { return m_data[1];}
  T& z() { return m_data[2];}


  // cylindrical coordinate system
  // to-do: implement
  const T& r() const { return T();}
  const T& phi() const { return T();}
  T& r() { return T();}
  T& phi() { return T();}


  // spherical coordinate system
  // to-do: implement
  const T& rSpherical() const { return T();}
  const T& phiSpherical() const { return T();}
  T& psi() { return T();}
  T& rSpherical() { return T();}
  T& phiSpherical() { return T();}
  const T& psi() const { return T();}

  // access to underlying data
  T& operator[](unsigned int i) {return m_data[i];}
  const T& operator[](unsigned int i) const {return m_data[i];}

 private:
  T m_data[3];
};

template <typename T>
std::ostream& operator << (std::ostream& out, const CoordSystemXYZ<T>& coords)
{
  return out << "CoordSystemXYZ( " << coords.x() << ", " << coords.y() << ", " << coords.z() << ")";
}

} // namespace Math

#endif // MATH_COORDSYSTEM3D_H__
