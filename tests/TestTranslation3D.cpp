//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestTranslation3D
#include <boost/test/unit_test.hpp>
#include <vector>
#include <numeric>
#include <functional>
#include "minimath/translation3d.hpp"
#include "minimath/point3d.hpp"

namespace
{
using namespace minimath;
}

BOOST_AUTO_TEST_SUITE(TestTranslation3D)

BOOST_AUTO_TEST_CASE(testInstantiation)
{
    translation3d<double> displ1, displ2;
}

BOOST_AUTO_TEST_CASE(testDefaultEquality)
{
    BOOST_CHECK(translation3d<double>() == translation3d<double>());
}

BOOST_AUTO_TEST_CASE(testCopyConstruction)
{
    translation3d<double> displ1;
    translation3d<double> displ2(displ1);
    BOOST_CHECK(displ1==displ2);
}

BOOST_AUTO_TEST_CASE(testAssignment)
{
    translation3d<double> displ1, displ2;
    displ2 = displ1;
    BOOST_CHECK(displ1==displ2);
}

BOOST_AUTO_TEST_CASE(testNullTranslation) 
{
    pointxyzd p(11, 22, 33);
    BOOST_CHECK(pointxyzd(11,22,33) == translation3d<double>()*p);
}

BOOST_AUTO_TEST_CASE(testTranslatePoint) 
{
    for (int i = 0; i < 100; ++i)
    {
        pointxyzd p(11, 22, 33);
        translation3d<double> t1(pointxyzd(i, i, i));
        BOOST_CHECK(pointxyzd(11+i, 22+i, 33+i) == t1*p);
        translation3d<double> t2(pointxyzd(-i, -i, -i));
        BOOST_CHECK(pointxyzd(11-i, 22-i, 33-i) == t2*p);
    }
}

BOOST_AUTO_TEST_CASE(testCompoundTranslation)
{
    // make a vector of many translations
    std::vector<translation3d<double> > v;
    int sum = 0;
    for (int i = 0; i<10; ++i)
    {
        sum += i;
        v.push_back(translation3d<double>(pointxyzd(i,i,i)));
    }
    // multiply all the translations together
    translation3d<double> t = std::accumulate(v.begin(), v.end(),
                                              translation3d<double>(), 
                                              std::multiplies<translation3d<double> >());
    BOOST_CHECK(pointxyzd(sum, sum, sum) == t*pointxyzd());
}

BOOST_AUTO_TEST_CASE(testInverse)
{
    translation3d<double> t0(pointxyzd(1., 2., 3.));
    BOOST_CHECK(t0.inverse() == translation3d<double>(pointxyzd(-1., -2., -3.)));
}
BOOST_AUTO_TEST_CASE(testInvert)
{
    translation3d<double> t0(pointxyzd(1., 2., 3.));
    t0.invert();
    BOOST_CHECK(t0 == translation3d<double>(pointxyzd(-1., -2., -3.)));
}

BOOST_AUTO_TEST_SUITE_END()
