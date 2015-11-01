//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestTransform3D
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include "minimath/rotation3d.hpp"
#include "minimath/transform3d.hpp"
#include "minimath/point3d.hpp"
#include "minimath/geom3d_ops.hpp"
#include "TestRotation3DUtils.h"

using namespace minimath;

namespace
{
struct setup
{
    setup() { std::cout << std::setprecision(18); }
};

}

BOOST_FIXTURE_TEST_SUITE(TestTransform3D, setup)

BOOST_AUTO_TEST_CASE(testInstantiation)
{
  rotation3d<double> rot1, rot2;
}

BOOST_AUTO_TEST_CASE(testDefaultEquality)
{
  BOOST_CHECK(rotation3d<double>()==rotation3d<double>());
}

BOOST_AUTO_TEST_CASE(testDefaultIsIdentity)
{
  transform3d<double> t;
  BOOST_CHECK(p100 == t*p100);
  BOOST_CHECK(p010 == t*p010);
  BOOST_CHECK(p001 == t*p001);
  BOOST_CHECK(p111 == t*p111);
}

BOOST_AUTO_TEST_CASE(testCopyConstruction)
{
  rotation3d<double> rot1;
  rotation3d<double> rot2(rot1);
  BOOST_CHECK(rot1 == rot2);
}

BOOST_AUTO_TEST_CASE(testAssignment)
{
  rotation3d<double> rot1, rot2;
  rot2 = rot1;
  BOOST_CHECK(rot1 == rot2);

}

BOOST_AUTO_TEST_CASE(testTranslation)
{
  transform3d<double> transf(translation3d<double>(111., 222., 333.));
  pointxyzd p;
  p = transf*p;
  BOOST_CHECK(p==pointxyzd(111., 222., 333.));

}

BOOST_AUTO_TEST_CASE(testRotation3D)
{
  rotation3d<double> rot;
  transform3d<double> transf(rot);
  pointxyzd p;
  p = transf*p;
  BOOST_CHECK(p==pointxyzd());
}

BOOST_AUTO_TEST_CASE(testRotationX45)
{
  rotation3d<double> rot(rotation3dx<double>(PI/4.));
  transform3d<double> transf(rot);
  pointxyzd pTest = transf*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = transf*p010;
  BOOST_CHECK(pTest == pointxyzd(0., cos45, cos45));

  pTest = transf*p001;
  BOOST_CHECK(pTest == pointxyzd(0., -cos45, cos45));
}


BOOST_AUTO_TEST_CASE(testRotationX90)
{
  rotation3d<double> rot(rotation3dx<double>(PI/2.));
  transform3d<double> transf(rot);
  pointxyzd pTest = transf*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = transf*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));

  pTest = transf*p001;
  BOOST_CHECK(pTest == pointxyzd(0., -1., 0.));
}

BOOST_AUTO_TEST_CASE(testRotationX180)
{
  rotation3d<double> rot(rotation3dx<double>(1.*PI));
  transform3d<double> transf(rot);
  pointxyzd pTest = transf*p100;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));

  pTest = transf*p010;
  BOOST_CHECK(pTest == pointxyzd(0., -1, 0));

  pTest = transf*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0, -1));
}

BOOST_AUTO_TEST_CASE(testRotationY45)
{
  rotation3d<double> rot(rotation3dy<double>(PI/4.)); 
  transform3d<double> transf(rot);
  pointxyzd pTest = transf*p100;
  BOOST_CHECK(pTest == pointxyzd(cos45, 0., -cos45));

  pTest = transf*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = transf*p001;
  BOOST_CHECK(pTest == pointxyzd(cos45, 0., cos45));
}


BOOST_AUTO_TEST_CASE(testRotationY90)
{
  rotation3d<double> rot(rotation3dy<double>(PI/2.));
  transform3d<double> transf(rot);
  pointxyzd pTest = transf*p100;
  BOOST_CHECK(pTest == pointxyzd(0., 0., -1.));

  pTest = transf*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = transf*p001;
  BOOST_CHECK(pTest == pointxyzd(1., 0., 0.));
}

BOOST_AUTO_TEST_CASE(testRotationY180)
{
  rotation3d<double> rot(rotation3dy<double>(1.*PI));
  transform3d<double> transf(rot);
  pointxyzd pTest = transf*p100;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = transf*p010;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = transf*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., -1.));
}

BOOST_AUTO_TEST_CASE(testRotationZ45)
{
  rotation3d<double> rot(rotation3dz<double>(PI/4.));
  transform3d<double> transf(rot);
  pointxyzd pTest = transf*p100;
  BOOST_CHECK(pTest == pointxyzd(cos45, cos45, 0.));

  pTest = transf*p010;
  BOOST_CHECK(pTest == pointxyzd(-cos45, cos45, 0.));

  pTest = transf*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testRotationZ90)
{
  rotation3d<double> rot(rotation3dz<double>(PI/2.));
  transform3d<double> transf(rot);
  pointxyzd pTest = transf*p100;
  BOOST_CHECK(pTest == pointxyzd(0., 1., 0.));

  pTest = transf*p010;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = transf*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}

BOOST_AUTO_TEST_CASE(testRotationZ180)
{
  rotation3d<double> rot(rotation3dz<double>(1.*PI));
  transform3d<double> transf(rot);
  pointxyzd pTest = transf*p100;
  BOOST_CHECK(pTest == pointxyzd(-1., 0., 0.));

  pTest = transf*p010;
  BOOST_CHECK(pTest == pointxyzd(0., -1., 0.));

  pTest = transf*p001;
  BOOST_CHECK(pTest == pointxyzd(0., 0., 1.));
}


BOOST_AUTO_TEST_CASE(testNullRotationAndTranslation)
{
  transform3d<double> transf(rotation3d<double>(), translation3d<double>(111., 222, 333.));
  pointxyzd p;
  p = transf*p;
  BOOST_CHECK(p==pointxyzd(111., 222., 333.));
}

BOOST_AUTO_TEST_CASE(testRotationXAndTranslation)
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    rotation3d<double> rot(rotation3dx<double>(PI/i));
    transform3d<double> transf(rot, translation3d<double>(111., 222, 333.));
    pointxyzd translation(111.,222.,333.);
    pointxyzd pTest = transf*p100;
    BOOST_CHECK(minimath::equal(pTest, rot*p100 + translation));

    pTest = transf*p010;
    bool test = minimath::equal(pTest, rot*p010 + translation);
    if (!test) {
      std::cout << "\nFail i = " << i << " pTest = " << pTest
          << " rot*p010 = " << (rot*p010) << "\n"; 
      std::cout << " rot*p010 + trans = " << (rot*p010 + translation) << "\n"; 
    }

    BOOST_CHECK(minimath::equal(pTest, rot*p010 + translation));

    pTest = transf*p001;
    BOOST_CHECK(minimath::equal(pTest,rot*p001 + translation));
  }
}

BOOST_AUTO_TEST_CASE(testRotationYAndTranslation)
{
  for (unsigned int i = 1; i<9; ++i)
  {
    rotation3d<double> rot(rotation3dy<double>(PI/i));
    transform3d<double> transf(rot, translation3d<double>(111., 222, 333.));
    pointxyzd translation(111.,222.,333.);
    pointxyzd pTest = transf*p100;
    BOOST_CHECK(minimath::equal(pTest, rot*p100 + translation));

    pTest = transf*p010;
    BOOST_CHECK(minimath::equal(pTest, rot*p010 + translation));

    pTest = transf*p001;
    BOOST_CHECK(minimath::equal(pTest, rot*p001 + translation));
  }
}

BOOST_AUTO_TEST_CASE(testRotationZAndTranslation)
{
  for (unsigned int i = 1; i<9; ++i)
  {
    rotation3d<double> rot(rotation3dz<double>(PI/i));
    transform3d<double> transf(rot, translation3d<double>(111., 222, 333.));
    pointxyzd translation(111.,222.,333.);
    pointxyzd pTest = transf*p100;
    BOOST_CHECK(minimath::equal(pTest, rot*p100 + translation));

    pTest = transf*p010;
    BOOST_CHECK(minimath::equal(pTest, rot*p010 + translation));

    pTest = transf*p001;
    BOOST_CHECK(minimath::equal(pTest, rot*p001 + translation));
  }
}

BOOST_AUTO_TEST_CASE(testTranslationAndNullRotation)
{
  transform3d<double> transf(translation3d<double>(111., 222, 333.), rotation3d<double>());
  pointxyzd p;
  p = transf*p;
  BOOST_CHECK(p==pointxyzd(111., 222., 333.));
}


BOOST_AUTO_TEST_CASE(testTranslationAndRotationX)
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    rotation3d<double> rot(rotation3dx<double>(PI/i));
    pointxyzd translation(999.,999.,999.);
    transform3d<double> transf(translation3d<double>(translation), rot);

    pointxyzd pTest = transf*p100;

    pointxyzd res100 = rot*translation + rot*p100;
    BOOST_CHECK(minimath::equal(pTest, res100));

    pTest = transf*p010;
    pointxyzd res010 = rot*translation + rot*p010;
    BOOST_CHECK(minimath::equal(pTest, res010));

    pTest = transf*p001;
    pointxyzd res001 = rot*translation + rot*p001;
    BOOST_CHECK(minimath::equal(pTest, res001));

  }

}

BOOST_AUTO_TEST_CASE(testTranslationAndRotationY)
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    rotation3d<double> rot(rotation3dy<double>(PI/i));
    pointxyzd translation(999.,999.,999.);
    transform3d<double> transf(translation3d<double>(translation), rot);

    pointxyzd pTest = transf*p100;
    pointxyzd res100 = rot*translation + rot*p100;
    BOOST_CHECK(minimath::equal(pTest, res100, 200));

    pTest = transf*p010;
    pointxyzd res010 = rot*translation + rot*p010;
    BOOST_CHECK(minimath::equal(pTest, res010));

    pTest = transf*p001;
    pointxyzd res001 = rot*translation + rot*p001;
    BOOST_CHECK(minimath::equal(pTest, res001));

  }

}

BOOST_AUTO_TEST_CASE(testTranslationAndRotationZ)
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    rotation3d<double> rot(rotation3dz<double>(PI/i));
    pointxyzd translation(999.,999.,999.);
    transform3d<double> transf(translation3d<double>(translation), rot);

    pointxyzd pTest = transf*p100;
    pointxyzd res100 = rot*translation + rot*p100;
    BOOST_CHECK(minimath::equal(pTest, res100, 2000));

    pTest = transf*p010;
    pointxyzd res010 = rot*translation + rot*p010;
    BOOST_CHECK(minimath::equal(pTest, res010));

    pTest = transf*p001;
    pointxyzd res001 = rot*translation + rot*p001;
    BOOST_CHECK(minimath::equal(pTest, res001));
  }
}

// test that a multiplication of Transform3Ds is the same as applying
// the individual transformations to a point one by one.
// Since we are chaining many operations, we use a "loose" tolerance of
// ~1000 epsilons.
BOOST_AUTO_TEST_CASE(testMultiplication)
{
  for (unsigned int i = 0; i < 10; ++i)
  {

    // get some random rotations and translations
    rotation3d<double> rot0 = TestUtils::randomRotation();
    rotation3d<double> rot1 = TestUtils::randomRotation();
    rotation3d<double> rot2 = TestUtils::randomRotation();
    translation3d<double> transl0 = TestUtils::randomTranslation(100.);
    translation3d<double> transl1 = TestUtils::randomTranslation(10.);
    translation3d<double> transl2 = TestUtils::randomTranslation(50.);

    // multiply the rotations and translations together
    transform3d<double> trans = transform3d<double>(rot0)*transform3d<double>(transl0)*transform3d<double>(rot1)*transform3d<double>(transl1)*transform3d<double>(rot2)*transform3d<double>(transl2);

    // get a sets of random points
    for (unsigned int j = 0; j < 10; ++j)
    {
      pointxyzd r = TestUtils::randomPoint(999);
      pointxyzd p0 = trans*r;
      pointxyzd p1 = transl2*r;
      p1 = rot2*p1;
      p1 = transl1*p1;
      p1 = rot1*p1;
      p1 = transl0*p1;
      p1 = rot0*p1;
      // check the resulting transformation is equivalent to the
      // product of transformations, by applying to the random points.

      BOOST_CHECK(minimath::equal(p0,p1, 2048));
    }
  }
}

BOOST_AUTO_TEST_CASE(testInverse)
{
  BOOST_CHECK(TestUtils::testInverseTransform3D<rotation3dx<double> >());
  BOOST_CHECK(TestUtils::testInverseTransform3D<rotation3dy<double> >());
  BOOST_CHECK(TestUtils::testInverseTransform3D<rotation3dz<double> >());
}

BOOST_AUTO_TEST_CASE(testInvert)
{
  BOOST_CHECK(TestUtils::testInvertTransform3D<rotation3dx<double> >());
  BOOST_CHECK(TestUtils::testInvertTransform3D<rotation3dy<double> >());
  BOOST_CHECK(TestUtils::testInvertTransform3D<rotation3dz<double> >());
}

BOOST_AUTO_TEST_SUITE_END()
