#ifndef TESTS_DEFINES_H_
#define TESTS_DEFINES_H_

#include "Math/Point3D.h"
#include "Math/type_traits.hpp"

const double cos45 = std::sqrt(2)/2.;
const double PI = std::atan(1.0)*4;

using Math::PointXYZD;



// custom point type
struct PointXYZD_
{
    typedef double value_type;

    PointXYZD_(double x, double y, double z) : x_(x), y_(y), z_(z) {}

    template <typename P>
    PointXYZD_(const P& p) : x_(p.x()), y_(p.y()), z_(p.z()) {}

    double x() const {return x_;}
    double y() const {return y_;}
    double z() const {return z_;}

 private:
    double x_, y_, z_;
};

inline bool operator==(const PointXYZD_& lhs, const PointXYZD_& rhs)
{
    return Math::equal(lhs, rhs, 1);
    //return lhs.x()==rhs.x() && lhs.y()==rhs.y() && lhs.z()==rhs.z();
}

inline std::ostream& operator << (std::ostream& out, const PointXYZD_& point)
{
  return out << "Point3D XYZ( " << point.x() << ", " << point.y() << ", " << point.z() << ")";
}

#ifndef CUSTOM_POINT
// reference points
const Math::PointXYZD p000(0.,0.,0);
const Math::PointXYZD p100(1.,0.,0);
const Math::PointXYZD p010(0.,1.,0);
const Math::PointXYZD p001(0.,0.,1);
const Math::PointXYZD p110(1.,1.,0);
const Math::PointXYZD p101(1.,0.,1);
const Math::PointXYZD p011(0.,1.,1);
const Math::PointXYZD p111(1.,1.,1);

#else
// custom reference points
const PointXYZD_ p000(0.,0.,0);
const PointXYZD_ p100(1.,0.,0);
const PointXYZD_ p010(0.,1.,0);
const PointXYZD_ p001(0.,0.,1);
const PointXYZD_ p110(1.,1.,0);
const PointXYZD_ p101(1.,0.,1);
const PointXYZD_ p011(0.,1.,1);
const PointXYZD_ p111(1.,1.,1);

#endif

#endif
