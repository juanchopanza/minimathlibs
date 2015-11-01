//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestAlignment
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "minimath/rotation3d.hpp"
#include "minimath/transform3d.hpp"
#include "minimath/point3d.hpp"
#include "minimath/geom3d_ops.hpp"

#include "Defines.h"
#include <tr1/array>

using namespace minimath;

namespace
{
// check that results of calculated transformation and
// reference transformation are the same to within 64 epsilons.
template <typename T>
void checkTransformation(const T& transf)
{
  pointxyzd pA = transf*p100;
  pointxyzd pB = transf*p010;
  pointxyzd pC = transf*p001;
  bool success = true;

  typedef std::tr1::array<pointxyzd, 2> PointXYZDPair;

  PointXYZDPair p0 = { {p100, pA} };
  PointXYZDPair p1 = { {p010, pB} };
  PointXYZDPair p2 = { {p001, pC} };
  std::tr1::array<PointXYZDPair, 3> pointPairs = { {p0, p1, p2} };

  transform3d<double> transf1 = transformation<double>(pointPairs.begin(),
                                                       pointPairs.end(),
                                                       success);

  BOOST_CHECK(success);
  BOOST_CHECK(minimath::equal(transf1*p100, pA, 128u));
  BOOST_CHECK(minimath::equal(transf1*p010, pB, 128u));
  BOOST_CHECK(minimath::equal(transf1*p001, pC, 64u));

}

template <typename R>
void checkRotationAndTranslation()
{
  for (int i = 1; i < 9;  ++i) {
    double x = std::rand()%100;
    double y = std::rand()%100;
    double z = std::rand()%100;
    translation3d<double> transl(pointxyzd(x,y,z));
    rotation3d<double> rot(R(PI/i));
    transform3d<double> transf(rot, transl);
    checkTransformation(transf);
  }
}

template <typename R>
void checkTranslationAndRotation()
{
  for (int i = 1; i < 9;  ++i) {
    double x = std::rand()%100;
    double y = std::rand()%100;
    double z = std::rand()%100;
    translation3d<double> transl(pointxyzd(x,y,z));
    rotation3d<double> rot(R(PI/i));
    transform3d<double> transf(transl, rot);
    checkTransformation(transf);
  }
}


} // anonymous namespace

BOOST_AUTO_TEST_SUITE(test_awesome_grower)

BOOST_AUTO_TEST_CASE(testTranslation)
{
  // rotate reference points
  translation3d<double> transl(pointxyzd(100, 100, 100));
  checkTransformation(transl);
}

BOOST_AUTO_TEST_CASE(testRotation)
{
  // rotate reference points
  rotation3dzyx<double>  rot(PI/4, 0, PI/4);
  checkTransformation(rot);
}

BOOST_AUTO_TEST_CASE(testRotation3DXAndTranslation)
{
  checkRotationAndTranslation<rotation3dx<double> >();
}

BOOST_AUTO_TEST_CASE(testRotation3DYAndTranslation)
{
  checkRotationAndTranslation<rotation3dy<double> >();
}

BOOST_AUTO_TEST_CASE(testRotation3DZAndTranslation)
{
  checkRotationAndTranslation<rotation3dz<double> >();
}

BOOST_AUTO_TEST_CASE(testTranslationAndRotation3DX)
{
  checkTranslationAndRotation<rotation3dx<double> >();
}

BOOST_AUTO_TEST_CASE(testTranslationAndRotation3DY)
{
  checkTranslationAndRotation<rotation3dy<double> >();
}

BOOST_AUTO_TEST_CASE(testTranslationAndRotation3DZ)
{
  checkTranslationAndRotation<rotation3dz<double> >();
}

BOOST_AUTO_TEST_SUITE_END()
