//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//

#ifndef TESTS_TRANSFORM3D_H__
#define TESTS_TRANSFORM3D_H__

#include <iostream>
#include <iomanip>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Rotation3D.h"
#include "Math/Transform3D.h"
#include "Math/Point3D.h"

namespace {
  using Math::Rotation3D;
  using Math::Rotation3DX;
  using Math::Rotation3DY;
  using Math::Rotation3DZ;

  using Math::Translation3D;
  using Math::Transform3D;
  using Math::PointXYZD;
}

class TestTransform3D : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestTransform3D);
  CPPUNIT_TEST(testInstantiation);
  CPPUNIT_TEST(testDefaultEquality);
  CPPUNIT_TEST(testCopyConstruction);
  CPPUNIT_TEST(testAssignment);
  CPPUNIT_TEST(testTranslation);
  CPPUNIT_TEST(testRotation3D);
  CPPUNIT_TEST(testRotationX45);
  CPPUNIT_TEST(testRotationX90);
  CPPUNIT_TEST(testRotationX180);
  CPPUNIT_TEST(testRotationY45);
  CPPUNIT_TEST(testRotationY90);
  CPPUNIT_TEST(testRotationY180);
  CPPUNIT_TEST(testRotationZ45);
  CPPUNIT_TEST(testRotationZ90);
  CPPUNIT_TEST(testRotationZ180);
  CPPUNIT_TEST(testNullRotationAndTranslation);
  CPPUNIT_TEST(testRotationXAndTranslation);
  CPPUNIT_TEST(testRotationYAndTranslation);
  CPPUNIT_TEST(testRotationZAndTranslation);

  CPPUNIT_TEST(testTranslationAndNullRotation);
  CPPUNIT_TEST(testTranslationAndRotationX);
  CPPUNIT_TEST(testTranslationAndRotationY);
  CPPUNIT_TEST(testTranslationAndRotationZ);


  CPPUNIT_TEST_SUITE_END();

 public:
  
  void setUp()
  {
    std::cout << std::setprecision(18);
    p100 = PointXYZD(1,0,0);
    p010 = PointXYZD(0,1,0);
    p001 = PointXYZD(0,0,1);
    cos45 = std::sqrt(2)/2;
    PI = std::atan(1.0)*4;
  }

 private:

  PointXYZD p100, p010, p001; // reference points 
  double cos45;
  double PI;

 protected:

  void testInstantiation()
  {
    Rotation3D rot1, rot2;
  }

  void testDefaultEquality()
  {
    CPPUNIT_ASSERT(Rotation3D()==Rotation3D());
  }

  void testCopyConstruction()
  {
    Rotation3D rot1;
    Rotation3D rot2(rot1);
    CPPUNIT_ASSERT(rot1 == rot2);
  }

  void testAssignment()
  {
    Rotation3D rot1, rot2;
    rot2 = rot1;
    CPPUNIT_ASSERT(rot1 == rot2);

  }

  void testTranslation()
  {
    Transform3D transf(Translation3D(111., 222., 333.));
    PointXYZD p;
    p = transf*p;
    CPPUNIT_ASSERT(p==PointXYZD(111., 222., 333.));

  }

  void testRotation3D()
  {
    Rotation3D rot;
    Transform3D transf (rot);
    PointXYZD p;
    p = transf*p;
    CPPUNIT_ASSERT(p==PointXYZD());
  }

  void testRotationX45()
  {
    Rotation3DX rot(PI/4.);
    Transform3D transf(rot);
    PointXYZD pTest = transf*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = transf*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., cos45, cos45));

    pTest = transf*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -cos45, cos45));
  }


  void testRotationX90()
  {
    Rotation3DX rot(PI/2.);
    Transform3D transf(rot);
    PointXYZD pTest = transf*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = transf*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));

    pTest = transf*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));
  }

  void testRotationX180()
  {
    Rotation3DX rot(PI);
    Transform3D transf(rot);
    PointXYZD pTest = transf*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));

    pTest = transf*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1, 0));

    pTest = transf*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0, -1));
  }

  void testRotationY45()
  {
    Rotation3DY rot(PI/4.); 
    Transform3D transf(rot);
    PointXYZD pTest = transf*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0., -cos45));

    pTest = transf*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = transf*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, 0., cos45));
  }


  void testRotationY90()
  {
    Rotation3DY rot(PI/2.);
    Transform3D transf(rot);
    PointXYZD pTest = transf*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));

    pTest = transf*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = transf*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(1., 0., 0.));
  }

  void testRotationY180()
  {
    Rotation3DY rot(PI);
    Transform3D transf(rot);
    PointXYZD pTest = transf*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = transf*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = transf*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., -1.));
  }

  void testRotationZ45()
  {
    Rotation3DZ rot(PI/4.);
    Transform3D transf(rot);
    PointXYZD pTest = transf*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(cos45, cos45, 0.));

    pTest = transf*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(-cos45, cos45, 0.));

    pTest = transf*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

  void testRotationZ90()
  {
    Rotation3DZ rot(PI/2.);
    Transform3D transf(rot);
    PointXYZD pTest = transf*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 1., 0.));

    pTest = transf*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = transf*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }

  void testRotationZ180()
  {
    Rotation3DZ rot(PI);
    Transform3D transf(rot);
    PointXYZD pTest = transf*p100;
    CPPUNIT_ASSERT(pTest == PointXYZD(-1., 0., 0.));

    pTest = transf*p010;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., -1., 0.));

    pTest = transf*p001;
    CPPUNIT_ASSERT(pTest == PointXYZD(0., 0., 1.));
  }


  void testNullRotationAndTranslation()
  {
    Transform3D transf(Rotation3D(), Translation3D(111., 222, 333.));
    PointXYZD p;
    p = transf*p;
    CPPUNIT_ASSERT(p==PointXYZD(111., 222., 333.));
  }

  void testRotationXAndTranslation()
  {
    for (unsigned int i = 1; i<9; ++i) 
    {
      Rotation3DX rot(PI/i);
      Transform3D transf(rot, Translation3D(111., 222, 333.));
      PointXYZD translation(111.,222.,333.);
      PointXYZD pTest = transf*p100;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, rot*p100 + translation));

      pTest = transf*p010;
      bool test = Math::equalXYZ(pTest, rot*p010 + translation);
      if (!test) {
        std::cout << "\nFail i = " << i << " pTest = " << pTest
                  << " rot*p010 = " << (rot*p010) << "\n"; 
        std::cout << " rot*p010 + trans = " << (rot*p010 + translation) << "\n"; 
      }

      CPPUNIT_ASSERT(Math::equalXYZ(pTest, rot*p010 + translation));

      pTest = transf*p001;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest,rot*p001 + translation));
    }
  }

  void testRotationYAndTranslation()
  {
    for (unsigned int i = 1; i<9; ++i)
    {
      Rotation3DY rot(PI/i);
      Transform3D transf(rot, Translation3D(111., 222, 333.));
      PointXYZD translation(111.,222.,333.);
      PointXYZD pTest = transf*p100;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, rot*p100 + translation));

      pTest = transf*p010;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, rot*p010 + translation));

      pTest = transf*p001;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, rot*p001 + translation));
    }
  }

  void testRotationZAndTranslation()
  {
    for (unsigned int i = 1; i<9; ++i)
    {
      Rotation3DZ rot(PI/i);
      Transform3D transf(rot, Translation3D(111., 222, 333.));
      PointXYZD translation(111.,222.,333.);
      PointXYZD pTest = transf*p100;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, rot*p100 + translation));

      pTest = transf*p010;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, rot*p010 + translation));

      pTest = transf*p001;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, rot*p001 + translation));
    }
  }

  void testTranslationAndNullRotation()
  {
    Transform3D transf(Translation3D(111., 222, 333.), Rotation3D());
    PointXYZD p;
    p = transf*p;
    CPPUNIT_ASSERT(p==PointXYZD(111., 222., 333.));
  }


  void testTranslationAndRotationX()
  {
    for (unsigned int i = 1; i<9; ++i) 
    {
      Rotation3DX rot(PI/i);
      PointXYZD translation(999.,999.,999.);
      Transform3D transf(Translation3D(translation), rot);

      PointXYZD pTest = transf*p100;
      bool test = Math::equalXYZ(pTest, (rot*translation) + rot*p100, 2);
      if (!test) {
        std::cout << "\nFail i = " << i 
                  << "\n pTest = " << pTest
                  << "\n rot*p100 = " << (rot*p100) 
                  << "\n rot*trans = " << (rot*translation); 
        std::cout << "\n rot*trans + rot*p100 = " << (rot*translation + rot*p100 ) << "\n"; 
      }
      PointXYZD res100 = rot*translation + rot*p100;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, res100));

      pTest = transf*p010;
      PointXYZD res010 = rot*translation + rot*p010;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, res010));

      pTest = transf*p001;
      PointXYZD res001 = rot*translation + rot*p001;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, res001));

    }

  }
 
  void testTranslationAndRotationY()
  {
    for (unsigned int i = 1; i<9; ++i) 
    {
      Rotation3DY rot(PI/i);
      PointXYZD translation(999.,999.,999.);
      Transform3D transf(Translation3D(translation), rot);

      PointXYZD pTest = transf*p100;
      PointXYZD res100 = rot*translation + rot*p100;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, res100, 200));

      pTest = transf*p010;
      PointXYZD res010 = rot*translation + rot*p010;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, res010));

      pTest = transf*p001;
      PointXYZD res001 = rot*translation + rot*p001;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, res001));

    }

  }

  void testTranslationAndRotationZ()
  {
    for (unsigned int i = 1; i<9; ++i) 
    {
      Rotation3DZ rot(PI/i);
      PointXYZD translation(999.,999.,999.);
      Transform3D transf(Translation3D(translation), rot);

      PointXYZD pTest = transf*p100;
      PointXYZD res100 = rot*translation + rot*p100;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, res100, 2000));

      pTest = transf*p010;
      PointXYZD res010 = rot*translation + rot*p010;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, res010));

      pTest = transf*p001;
      PointXYZD res001 = rot*translation + rot*p001;
      CPPUNIT_ASSERT(Math::equalXYZ(pTest, res001));
    }
  }

};



#endif

