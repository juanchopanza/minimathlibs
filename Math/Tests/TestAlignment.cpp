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

#include "Math/Rotation3D.h"
#include "Math/Transform3D.h"
#include "Math/Point3D.h"
#include "Math/Geom3DOps.h"

#include "Defines.h"
#include "TestAlignment.h"
#include <tr1/array>

using namespace Math;

namespace
{
// check that results of calculated transformation and
// reference transformation are the same to within 64 epsilons.
template <typename T>
void testTransformation(const T& transf)
{
  PointXYZD pA = transf*p100;
  PointXYZD pB = transf*p010;
  PointXYZD pC = transf*p001;
  bool success = true;

  typedef std::tr1::array<PointXYZD, 2> PointXYZDPair;

  PointXYZDPair p0 = { {p100, pA} };
  PointXYZDPair p1 = { {p010, pB} };
  PointXYZDPair p2 = { {p001, pC} };
  std::tr1::array<PointXYZDPair, 3> pointPairs = { {p0, p1, p2} };

  Transform3D<double> transf1 = transformation<double>(pointPairs.begin(),
                                                       pointPairs.end(),
                                                       success);

  CPPUNIT_ASSERT(success);
  CPPUNIT_ASSERT(Math::equal(transf1*p100, pA, 128u));
  CPPUNIT_ASSERT(Math::equal(transf1*p010, pB, 128u));
  CPPUNIT_ASSERT(Math::equal(transf1*p001, pC, 64u));

}

template <typename R>
void testRotationAndTranslation()
{
  for (int i = 1; i < 9;  ++i) {
    double x = std::rand()%100;
    double y = std::rand()%100;
    double z = std::rand()%100;
    Translation3D<double> transl(PointXYZD(x,y,z));
    Rotation3D<double> rot(R(PI/i));
    Transform3D<double> transf(rot, transl);
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
    Translation3D<double> transl(PointXYZD(x,y,z));
    Rotation3D<double> rot(R(PI/i));
    Transform3D<double> transf(transl, rot);
    testTransformation(transf);
  }
}


} // anonymous namespace

void TestAlignment::testTranslation()
{
  // rotate reference points
  Translation3D<double> transl(PointXYZD(100, 100, 100));
  testTransformation(transl);
}

void TestAlignment::testRotation()
{
  // rotate reference points
  Rotation3DZYX<double>  rot(PI/4, 0, PI/4);
  testTransformation(rot);
}

void TestAlignment::testRotation3DXAndTranslation()
{
  testRotationAndTranslation<Rotation3DX<double> >();
}

void TestAlignment::testRotation3DYAndTranslation()
{
  testRotationAndTranslation<Rotation3DY<double> >();
}

void TestAlignment::testRotation3DZAndTranslation()
{
  testRotationAndTranslation<Rotation3DZ<double> >();
}

void TestAlignment::testTranslationAndRotation3DX()
{
  testTranslationAndRotation<Rotation3DX<double> >();
}

void TestAlignment::testTranslationAndRotation3DY()
{
  testTranslationAndRotation<Rotation3DY<double> >();
}

void TestAlignment::testTranslationAndRotation3DZ()
{
  testTranslationAndRotation<Rotation3DZ<double> >();
}

