//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//

#ifndef TESTS_TRANSLATION3D_H__
#define TESTS_TRANSLATION3D_H__

#include <vector>
#include <numeric>
#include <functional>

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
  CPPUNIT_TEST(testCompoundTranslation);
  CPPUNIT_TEST(testInverse);
  CPPUNIT_TEST(testInvert);
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
    for (int i = 0; i < 100; ++i)
    {
      PointXYZD p(11, 22, 33);
      Translation3D t1(PointXYZD(i, i, i));
      CPPUNIT_ASSERT(PointXYZD(11+i, 22+i, 33+i) == t1*p);
      Translation3D t2(PointXYZD(-i, -i, -i));
      CPPUNIT_ASSERT(PointXYZD(11-i, 22-i, 33-i) == t2*p);
    }
  }

  void testCompoundTranslation()
  {
    // make a vector of many translations
    std::vector<Translation3D> v;
    int sum = 0;
    for (int i = 0; i<10; ++i)
    {
      sum += i;
      v.push_back(Translation3D(PointXYZD(i,i,i)));
    }
    // multiply all the translations together
    Translation3D t = std::accumulate(v.begin(), v.end(),
                                      Translation3D(), 
                                      std::multiplies<Translation3D>());
    CPPUNIT_ASSERT(PointXYZD(sum, sum, sum) == t*PointXYZD());
  }

  void testInverse()
  {
    Translation3D t0(PointXYZD(1., 2., 3.));
    CPPUNIT_ASSERT(t0.Inverse() == Translation3D(PointXYZD(-1., -2., -3.)));
  }
  void testInvert()
  {
    Translation3D t0(PointXYZD(1., 2., 3.));
    t0.Invert();
    CPPUNIT_ASSERT(t0 == Translation3D(PointXYZD(-1., -2., -3.)));
  }

};


#endif

