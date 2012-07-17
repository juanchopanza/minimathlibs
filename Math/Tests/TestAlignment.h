//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_TESTALIGNMENT_H__
#define TESTS_TESTALIGNMENT_H__

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
#include <tr1/array>

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

  typedef std::tr1::array<PointXYZD, 2> PointXYTPair;

  PointXYZDPair p0 = { {p100, pA} };
  PointXYZDPair p1 = { {p010, pB} };
  PointXYZDPair p2 = { {p001, pC} };
  std::tr1::array<PointXYZDPair, 3> pointPairs = { {p0, p1, p2} };

  Transform3D transf1 = transformation(pointPairs.begin(),
                                       pointPairs.end(),
                                       success);

  CPPUNIT_ASSERT(success);
  CPPUNIT_ASSERT(Math::equal(transf1*p100, pA, 64));
  CPPUNIT_ASSERT(Math::equal(transf1*p010, pB, 64));
  CPPUNIT_ASSERT(Math::equal(transf1*p001, pC, 64));

}

template <typename R>
void testRotationAndTranslation()
{
  for (int i = 1; i < 9;  ++i) {
    double x = std::rand()%100;
    double y = std::rand()%100;
    double z = std::rand()%100;
    Translation3D transl(PointXYZD(x,y,z));
    Rotation3D rot(R(PI/i));
    Transform3D transf(rot, transl);
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
    Translation3D transl(PointXYZD(x,y,z));
    Rotation3D rot(R(PI/i));
    Transform3D transf(transl, rot);
    testTransformation(transf);
  }
}


} // anonymous namespace

class TestAlignment : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestAlignment);
  CPPUNIT_TEST(testRotation);
  CPPUNIT_TEST(testTranslation);
  CPPUNIT_TEST(testRotation3DXAndTranslation);
  CPPUNIT_TEST(testRotation3DYAndTranslation);
  CPPUNIT_TEST(testRotation3DZAndTranslation);
  CPPUNIT_TEST(testTranslationAndRotation3DX);
  CPPUNIT_TEST(testTranslationAndRotation3DY);
  CPPUNIT_TEST(testTranslationAndRotation3DZ);
  CPPUNIT_TEST_SUITE_END();

  void testTranslation()
  {
    // rotate reference points
    Translation3D transl(PointXYZD(100, 100, 100));
    testTransformation(transl);
  }

  void testRotation()
  {
    // rotate reference points
    Rotation3DZYX rot(PI/4, 0, PI/4);
    testTransformation(rot);
  }

  void testRotation3DXAndTranslation()
  {
    testRotationAndTranslation<Rotation3DX>();
  }

  void testRotation3DYAndTranslation()
  {
    testRotationAndTranslation<Rotation3DY>();
  }

  void testRotation3DZAndTranslation()
  {
    testRotationAndTranslation<Rotation3DZ>();
  }

  void testTranslationAndRotation3DX()
  {
    testTranslationAndRotation<Rotation3DX>();
  }

  void testTranslationAndRotation3DY()
  {
    testTranslationAndRotation<Rotation3DY>();
  }

  void testTranslationAndRotation3DZ()
  {
    testTranslationAndRotation<Rotation3DZ>();
  }

};

#endif // TESTS_TESTALIGNMENT_H__
