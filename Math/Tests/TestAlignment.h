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

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Rotation3D.h"
#include "Math/Transform3D.h"
#include "Math/Point3D.h"
#include "Math/Geom3DOps.h"

#include "Defines.h"

class TestAlignment : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestAlignment);
  CPPUNIT_TEST(testRotation);
  CPPUNIT_TEST_SUITE_END();

  void testTranslation()
  {
    // rotate reference points
    Translation3D transl(PointXYZD(100, 100, 100));
    PointXYZD pA = transl*p100;
    PointXYZD pB = transl*p010;
    PointXYZD pC = transl*p001;
    bool success = true;
    Transform3D transf = transformation(std::make_pair(p100, pA),
                                        std::make_pair(p010, pB),
                                        std::make_pair(p001, pC),
                                        success);
    //std::cout << "\n" << transf << "\n";
    CPPUNIT_ASSERT(success);
    //CPPUNIT_ASSERT(true);
  }

  void testRotation()
  {
    // rotate reference points
    Rotation3DZYX rot(PI/4, 0, PI/4);
    PointXYZD pA = rot*p100;
    PointXYZD pB = rot*p010;
    PointXYZD pC = rot*p001;
    bool success = true;
    Transform3D transf = transformation(std::make_pair(p100, pA),
                                        std::make_pair(p010, pB),
                                        std::make_pair(p001, pC),
                                        success);
    //std::cout << "\n" << transf << "\n";
    CPPUNIT_ASSERT(success);
    CPPUNIT_ASSERT(transf*p100 == pA);
    CPPUNIT_ASSERT(transf*p010 == pB);
    CPPUNIT_ASSERT(transf*p001 == pC);
  }
};

#endif // TESTS_TESTALIGNMENT_H__
