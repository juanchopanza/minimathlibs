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
    PointXYZD_(double x, double y, double z)
    {
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
    }

    template <typename P>
    PointXYZD_(const P& p)
    {
        data_[0] = p.x();
        data_[1] = p.y();
        data_[2] = p.z();
    }

    double x() const {return data_[0];}
    double y() const {return data_[1];}
    double z() const {return data_[2];}
    double& operator[](std::size_t i) { return data_[i]; }
    const double& operator[](std::size_t i) const { return data_[i]; }
 private:
    double data_[3];
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


// reference points
const Math::PointXYZD p000(0.,0.,0);
const Math::PointXYZD p100(1.,0.,0);
const Math::PointXYZD p010(0.,1.,0);
const Math::PointXYZD p001(0.,0.,1);
const Math::PointXYZD p110(1.,1.,0);
const Math::PointXYZD p101(1.,0.,1);
const Math::PointXYZD p011(0.,1.,1);
const Math::PointXYZD p111(1.,1.,1);


/*
// custom reference points
const PointXYZD_ p000(0.,0.,0);
const PointXYZD_ p100(1.,0.,0);
const PointXYZD_ p010(0.,1.,0);
const PointXYZD_ p001(0.,0.,1);
const PointXYZD_ p110(1.,1.,0);
const PointXYZD_ p101(1.,0.,1);
const PointXYZD_ p011(0.,1.,1);
const PointXYZD_ p111(1.,1.,1);
*/

#endif
