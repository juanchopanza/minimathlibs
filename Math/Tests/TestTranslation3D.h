//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimath.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//

#ifndef TESTS_TRANSLATION3D_H__
#define TESTS_TRANSLATION3D_H__


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Translation3D.h"
#include "Math/Point3D.h"

namespace
{
  using Math::Translation3D;
  using Math::PointXYZD;
}

class TestTranslation3D : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestTranslation3D);
  CPPUNIT_TEST(testInstantiation);
  CPPUNIT_TEST(testDefaultEquality);
  CPPUNIT_TEST(testCopyConstruction);
  CPPUNIT_TEST(testAssignment);
  CPPUNIT_TEST(testNullTranslation);
  CPPUNIT_TEST(testTranslatePoint);
  CPPUNIT_TEST_SUITE_END();

 protected:

  void testInstantiation()
  {
    Translation3D displ1, displ2;
  }

  void testDefaultEquality()
  {
    CPPUNIT_ASSERT(Translation3D() == Translation3D());
  }

  void testCopyConstruction()
  {
    Translation3D displ1;
    Translation3D displ2(displ1);
    CPPUNIT_ASSERT(displ1==displ2);
  }

  void testAssignment()
  {
    Translation3D displ1, displ2;
    displ2 = displ1;
    CPPUNIT_ASSERT(displ1==displ2);
  }

  void testNullTranslation() {
    PointXYZD p(11, 22, 33);
    CPPUNIT_ASSERT(PointXYZD(11,22,33) == Translation3D()*p);
  }

  void testTranslatePoint() {
    PointXYZD p(11, 22, 33);
    Translation3D t(PointXYZD(100, 200, 300));
    CPPUNIT_ASSERT(PointXYZD(111, 222, 333) == t*p);
  }

};


#endif

