//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef GEOM3D_TRANSFORM3DOPS_H__
#define GEOM3D_TRANSFORM3DOPS_H__


namespace Geom3D {

template <typename Point>
Point operator*(const Transform3D& transform, const Point& point)
{
  return Point();
}
template <typename Point>
Point operator*(cont Point& point, const Transform3D& transform) 
{
  return Point();
}

} // namespace Geom3D

#endif // GEOM3D_TRANSFORM3DOPS_H__
