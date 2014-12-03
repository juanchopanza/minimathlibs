#ifndef TESTS_DEFINES_H_
#define TESTS_DEFINES_H_

#include "minimath/point3d.hpp"
#include "minimath/type_traits.hpp"

const double cos45 = std::sqrt(2)/2.;
const double PI = std::atan(1.0)*4;

using minimath::pointxyzd;



// custom point type
struct pointxyzd_
{
    typedef double value_type;

    pointxyzd_(double x, double y, double z) : x_(x), y_(y), z_(z) {}

    template <typename P>
    pointxyzd_(const P& p) : x_(p.x()), y_(p.y()), z_(p.z()) {}

    double x() const {return x_;}
    double y() const {return y_;}
    double z() const {return z_;}

 private:
    double x_, y_, z_;
};

inline bool operator==(const pointxyzd_& lhs, const pointxyzd_& rhs)
{
    return minimath::equal(lhs, rhs, 1);
}

inline std::ostream& operator << (std::ostream& out, const pointxyzd_& point)
{
  return out << "Point3D XYZ( " << point.x() << ", " << point.y() << ", " << point.z() << ")";
}

#ifndef CUSTOM_POINT
// reference points
const minimath::pointxyzd p000(0.,0.,0);
const minimath::pointxyzd p100(1.,0.,0);
const minimath::pointxyzd p010(0.,1.,0);
const minimath::pointxyzd p001(0.,0.,1);
const minimath::pointxyzd p110(1.,1.,0);
const minimath::pointxyzd p101(1.,0.,1);
const minimath::pointxyzd p011(0.,1.,1);
const minimath::pointxyzd p111(1.,1.,1);

#else
// custom reference points
const pointxyzd_ p000(0.,0.,0);
const pointxyzd_ p100(1.,0.,0);
const pointxyzd_ p010(0.,1.,0);
const pointxyzd_ p001(0.,0.,1);
const pointxyzd_ p110(1.,1.,0);
const pointxyzd_ p101(1.,0.,1);
const pointxyzd_ p011(0.,1.,1);
const pointxyzd_ p111(1.,1.,1);

#endif

#endif
