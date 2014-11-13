//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#include <iostream>
#include <iomanip>
#include <vector>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Rotation3D.h"
#include "Math/Transform3D.h"
#include "Math/Point3D.h"
#include "Math/Geom3DOps.h"

#include "TestRotation3DUtils.h"

#include "TestTransform3D.h"

using namespace Math;

void TestTransform3D::setUp()
{
  std::cout << std::setprecision(18);
}

void TestTransform3D::testInstantiation()
{
  Rotation3D<double> rot1, rot2;
}

void TestTransform3D::testDefaultEquality()
{
  CPPUNIT_ASSERT(Rotation3D<double>()==Rotation3D<double>());
}

void TestTransform3D::testDefaultIsIdentity()
{
  Transform3D<double> t;
  CPPUNIT_ASSERT(p100 == t*p100);
  CPPUNIT_ASSERT(p010 == t*p010);
  CPPUNIT_ASSERT(p001 == t*p001);
  CPPUNIT_ASSERT(p111 == t*p111);
}

void TestTransform3D::testCopyConstruction()
{
  Rotation3D<double> rot1;
  Rotation3D<double> rot2(rot1);
  CPPUNIT_ASSERT(rot1 == rot2);
}

void TestTransform3D::testAssignment()
{
  Rotation3D<double> rot1, rot2;
  rot2 = rot1;
  CPPUNIT_ASSERT(rot1 == rot2);

}

void TestTransform3D::testTranslation()
{
  Transform3D<double> transf(Translation3D<double>(111., 222., 333.));
  PointXYZD p;
  p = transf*p;
  CPPUNIT_ASSERT(p==PointXYZD(111., 222., 333.));

}

void TestTransform3D::testRotation3D()
{
  Rotation3D<double> rot;
  Transform3D<double> transf(rot);
  PointXYZD p;
  p = transf*p;
  CPPUNIT_ASSERT(p==PointXYZD());
}

void TestTransform3D::testRotationX45()
{
  Rotation3D<double> rot(Rotation3DX<double>(PI/4.));
  Transform3D<double> transf(rot);
  PointXYZD pTest = transf*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = transf*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., cos45, cos45));

  pTest = transf*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -cos45, cos45));
}


void TestTransform3D::testRotationX90()
{
  Rotation3D<double> rot(Rotation3DX<double>(PI/2.));
  Transform3D<double> transf(rot);
  PointXYZD pTest = transf*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = transf*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));

  pTest = transf*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));
}

void TestTransform3D::testRotationX180()
{
  Rotation3D<double> rot(Rotation3DX<double>(1.*PI));
  Transform3D<double> transf(rot);
  PointXYZD pTest = transf*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

  pTest = transf*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -1, 0));

  pTest = transf*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0, -1));
}

void TestTransform3D::testRotationY45()
{
  Rotation3D<double> rot(Rotation3DY<double>(PI/4.)); 
  Transform3D<double> transf(rot);
  PointXYZD pTest = transf*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0., -cos45));

  pTest = transf*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = transf*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0., cos45));
}


void TestTransform3D::testRotationY90()
{
  Rotation3D<double> rot(Rotation3DY<double>(PI/2.));
  Transform3D<double> transf(rot);
  PointXYZD pTest = transf*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));

  pTest = transf*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = transf*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));
}

void TestTransform3D::testRotationY180()
{
  Rotation3D<double> rot(Rotation3DY<double>(1.*PI));
  Transform3D<double> transf(rot);
  PointXYZD pTest = transf*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = transf*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = transf*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
}

void TestTransform3D::testRotationZ45()
{
  Rotation3D<double> rot(Rotation3DZ<double>(PI/4.));
  Transform3D<double> transf(rot);
  PointXYZD pTest = transf*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(cos45, cos45, 0.));

  pTest = transf*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(-cos45, cos45, 0.));

  pTest = transf*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestTransform3D::testRotationZ90()
{
  Rotation3D<double> rot(Rotation3DZ<double>(PI/2.));
  Transform3D<double> transf(rot);
  PointXYZD pTest = transf*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

  pTest = transf*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = transf*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}

void TestTransform3D::testRotationZ180()
{
  Rotation3D<double> rot(Rotation3DZ<double>(1.*PI));
  Transform3D<double> transf(rot);
  PointXYZD pTest = transf*p100;
  CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

  pTest = transf*p010;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

  pTest = transf*p001;
  CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
}


void TestTransform3D::testNullRotationAndTranslation()
{
  Transform3D<double> transf(Rotation3D<double>(), Translation3D<double>(111., 222, 333.));
  PointXYZD p;
  p = transf*p;
  CPPUNIT_ASSERT(p==PointXYZD(111., 222., 333.));
}

void TestTransform3D::testRotationXAndTranslation()
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    Rotation3D<double> rot(Rotation3DX<double>(PI/i));
    Transform3D<double> transf(rot, Translation3D<double>(111., 222, 333.));
    PointXYZD translation(111.,222.,333.);
    PointXYZD pTest = transf*p100;
    CPPUNIT_ASSERT(Math::equal(pTest, rot*p100 + translation));

    pTest = transf*p010;
    bool test = Math::equal(pTest, rot*p010 + translation);
    if (!test) {
      std::cout << "\nFail i = " << i << " pTest = " << pTest
          << " rot*p010 = " << (rot*p010) << "\n"; 
      std::cout << " rot*p010 + trans = " << (rot*p010 + translation) << "\n"; 
    }

    CPPUNIT_ASSERT(Math::equal(pTest, rot*p010 + translation));

    pTest = transf*p001;
    CPPUNIT_ASSERT(Math::equal(pTest,rot*p001 + translation));
  }
}

void TestTransform3D::testRotationYAndTranslation()
{
  for (unsigned int i = 1; i<9; ++i)
  {
    Rotation3D<double> rot(Rotation3DY<double>(PI/i));
    Transform3D<double> transf(rot, Translation3D<double>(111., 222, 333.));
    PointXYZD translation(111.,222.,333.);
    PointXYZD pTest = transf*p100;
    CPPUNIT_ASSERT(Math::equal(pTest, rot*p100 + translation));

    pTest = transf*p010;
    CPPUNIT_ASSERT(Math::equal(pTest, rot*p010 + translation));

    pTest = transf*p001;
    CPPUNIT_ASSERT(Math::equal(pTest, rot*p001 + translation));
  }
}

void TestTransform3D::testRotationZAndTranslation()
{
  for (unsigned int i = 1; i<9; ++i)
  {
    Rotation3D<double> rot(Rotation3DZ<double>(PI/i));
    Transform3D<double> transf(rot, Translation3D<double>(111., 222, 333.));
    PointXYZD translation(111.,222.,333.);
    PointXYZD pTest = transf*p100;
    CPPUNIT_ASSERT(Math::equal(pTest, rot*p100 + translation));

    pTest = transf*p010;
    CPPUNIT_ASSERT(Math::equal(pTest, rot*p010 + translation));

    pTest = transf*p001;
    CPPUNIT_ASSERT(Math::equal(pTest, rot*p001 + translation));
  }
}

void TestTransform3D::testTranslationAndNullRotation()
{
  Transform3D<double> transf(Translation3D<double>(111., 222, 333.), Rotation3D<double>());
  PointXYZD p;
  p = transf*p;
  CPPUNIT_ASSERT(p==PointXYZD(111., 222., 333.));
}


void TestTransform3D::testTranslationAndRotationX()
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    Rotation3D<double> rot(Rotation3DX<double>(PI/i));
    PointXYZD translation(999.,999.,999.);
    Transform3D<double> transf(Translation3D<double>(translation), rot);

    PointXYZD pTest = transf*p100;

    PointXYZD res100 = rot*translation + rot*p100;
    CPPUNIT_ASSERT(Math::equal(pTest, res100));

    pTest = transf*p010;
    PointXYZD res010 = rot*translation + rot*p010;
    CPPUNIT_ASSERT(Math::equal(pTest, res010));

    pTest = transf*p001;
    PointXYZD res001 = rot*translation + rot*p001;
    CPPUNIT_ASSERT(Math::equal(pTest, res001));

  }

}

void TestTransform3D::testTranslationAndRotationY()
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    Rotation3D<double> rot(Rotation3DY<double>(PI/i));
    PointXYZD translation(999.,999.,999.);
    Transform3D<double> transf(Translation3D<double>(translation), rot);

    PointXYZD pTest = transf*p100;
    PointXYZD res100 = rot*translation + rot*p100;
    CPPUNIT_ASSERT(Math::equal(pTest, res100, 200));

    pTest = transf*p010;
    PointXYZD res010 = rot*translation + rot*p010;
    CPPUNIT_ASSERT(Math::equal(pTest, res010));

    pTest = transf*p001;
    PointXYZD res001 = rot*translation + rot*p001;
    CPPUNIT_ASSERT(Math::equal(pTest, res001));

  }

}

void TestTransform3D::testTranslationAndRotationZ()
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    Rotation3D<double> rot(Rotation3DZ<double>(PI/i));
    PointXYZD translation(999.,999.,999.);
    Transform3D<double> transf(Translation3D<double>(translation), rot);

    PointXYZD pTest = transf*p100;
    PointXYZD res100 = rot*translation + rot*p100;
    CPPUNIT_ASSERT(Math::equal(pTest, res100, 2000));

    pTest = transf*p010;
    PointXYZD res010 = rot*translation + rot*p010;
    CPPUNIT_ASSERT(Math::equal(pTest, res010));

    pTest = transf*p001;
    PointXYZD res001 = rot*translation + rot*p001;
    CPPUNIT_ASSERT(Math::equal(pTest, res001));
  }
}

// test that a multiplication of Transform3Ds is the same as applying
// the individual transformations to a point one by one.
// Since we are chaining many operations, we use a "loose" tolerance of
// ~1000 epsilons.
void TestTransform3D::testMultiplication()
{
  for (unsigned int i = 0; i < 10; ++i)
  {

    // get some random rotations and translations
    Rotation3D<double> rot0 = TestUtils::randomRotation();
    Rotation3D<double> rot1 = TestUtils::randomRotation();
    Rotation3D<double> rot2 = TestUtils::randomRotation();
    Translation3D<double> transl0 = TestUtils::randomTranslation(100.);
    Translation3D<double> transl1 = TestUtils::randomTranslation(10.);
    Translation3D<double> transl2 = TestUtils::randomTranslation(50.);

    // multiply the rotations and translations together
    Transform3D<double> trans = Transform3D<double>(rot0)*Transform3D<double>(transl0)*Transform3D<double>(rot1)*Transform3D<double>(transl1)*Transform3D<double>(rot2)*Transform3D<double>(transl2);

    // get a sets of random points
    for (unsigned int j = 0; j < 10; ++j)
    {
      PointXYZD r = TestUtils::randomPoint(999);
      PointXYZD p0 = trans*r;
      PointXYZD p1 = transl2*r;
      p1 = rot2*p1;
      p1 = transl1*p1;
      p1 = rot1*p1;
      p1 = transl0*p1;
      p1 = rot0*p1;
      // check the resulting transformation is equivalent to the
      // product of transformations, by applying to the random points.

      CPPUNIT_ASSERT(Math::equal(p0,p1, 2048));
    }
  }
}

void TestTransform3D::testInverse()
{
  CPPUNIT_ASSERT(TestUtils::testInverseTransform3D<Rotation3DX<double> >());
  CPPUNIT_ASSERT(TestUtils::testInverseTransform3D<Rotation3DY<double> >());
  CPPUNIT_ASSERT(TestUtils::testInverseTransform3D<Rotation3DZ<double> >());
}

void TestTransform3D::testInvert()
{
  CPPUNIT_ASSERT(TestUtils::testInvertTransform3D<Rotation3DX<double> >());
  CPPUNIT_ASSERT(TestUtils::testInvertTransform3D<Rotation3DY<double> >());
  CPPUNIT_ASSERT(TestUtils::testInvertTransform3D<Rotation3DZ<double> >());
}

