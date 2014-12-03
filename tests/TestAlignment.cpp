//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "minimath/rotation3d.hpp"
#include "minimath/transform3d.hpp"
#include "minimath/point3d.hpp"
#include "minimath/geom3d_ops.hpp"

#include "Defines.h"
#include "TestAlignment.h"
#include <tr1/array>

using namespace minimath;

namespace
{
// check that results of calculated transformation and
// reference transformation are the same to within 64 epsilons.
template <typename T>
void testTransformation(const T& transf)
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

  CPPUNIT_ASSERT(success);
  CPPUNIT_ASSERT(minimath::equal(transf1*p100, pA, 128u));
  CPPUNIT_ASSERT(minimath::equal(transf1*p010, pB, 128u));
  CPPUNIT_ASSERT(minimath::equal(transf1*p001, pC, 64u));

}

template <typename R>
void testRotationAndTranslation()
{
  for (int i = 1; i < 9;  ++i) {
    double x = std::rand()%100;
    double y = std::rand()%100;
    double z = std::rand()%100;
    translation3d<double> transl(pointxyzd(x,y,z));
    rotation3d<double> rot(R(PI/i));
    transform3d<double> transf(rot, transl);
    testTransformation(transf);
  }
}

template <typename R>
void testTranslationAndRotation()
{
  for (int i = 1; i < 9;  ++i) {
    double x = std::rand()%100;
    double y = std::rand()%100;
    double z = std::rand()%100;
    translation3d<double> transl(pointxyzd(x,y,z));
    rotation3d<double> rot(R(PI/i));
    transform3d<double> transf(transl, rot);
    testTransformation(transf);
  }
}


} // anonymous namespace

void TestAlignment::testTranslation()
{
  // rotate reference points
  translation3d<double> transl(pointxyzd(100, 100, 100));
  testTransformation(transl);
}

void TestAlignment::testRotation()
{
  // rotate reference points
  rotation3dzyx<double>  rot(PI/4, 0, PI/4);
  testTransformation(rot);
}

void TestAlignment::testRotation3DXAndTranslation()
{
  testRotationAndTranslation<rotation3dx<double> >();
}

void TestAlignment::testRotation3DYAndTranslation()
{
  testRotationAndTranslation<rotation3dy<double> >();
}

void TestAlignment::testRotation3DZAndTranslation()
{
  testRotationAndTranslation<rotation3dz<double> >();
}

void TestAlignment::testTranslationAndRotation3DX()
{
  testTranslationAndRotation<rotation3dx<double> >();
}

void TestAlignment::testTranslationAndRotation3DY()
{
  testTranslationAndRotation<rotation3dy<double> >();
}

void TestAlignment::testTranslationAndRotation3DZ()
{
  testTranslationAndRotation<rotation3dz<double> >();
}

