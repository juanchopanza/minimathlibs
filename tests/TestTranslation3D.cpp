//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#include <vector>
#include <numeric>
#include <functional>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "minimath/translation3d.hpp"
#include "minimath/point3d.hpp"

#include "TestTranslation3D.h"

namespace
{
using namespace minimath;
}

void TestTranslation3D::testInstantiation()
{
  translation3d<double> displ1, displ2;
}

void TestTranslation3D::testDefaultEquality()
{
  CPPUNIT_ASSERT(translation3d<double>() == translation3d<double>());
}

void TestTranslation3D::testCopyConstruction()
{
  translation3d<double> displ1;
  translation3d<double> displ2(displ1);
  CPPUNIT_ASSERT(displ1==displ2);
}

void TestTranslation3D::testAssignment()
{
  translation3d<double> displ1, displ2;
  displ2 = displ1;
  CPPUNIT_ASSERT(displ1==displ2);
}

void TestTranslation3D::testNullTranslation() {
  pointxyzd p(11, 22, 33);
  CPPUNIT_ASSERT(pointxyzd(11,22,33) == translation3d<double>()*p);
}

void TestTranslation3D::testTranslatePoint() {
  for (int i = 0; i < 100; ++i)
  {
    pointxyzd p(11, 22, 33);
    translation3d<double> t1(pointxyzd(i, i, i));
    CPPUNIT_ASSERT(pointxyzd(11+i, 22+i, 33+i) == t1*p);
    translation3d<double> t2(pointxyzd(-i, -i, -i));
    CPPUNIT_ASSERT(pointxyzd(11-i, 22-i, 33-i) == t2*p);
  }
}

void TestTranslation3D::testCompoundTranslation()
{
  // make a vector of many translations
  std::vector<translation3d<double> > v;
  int sum = 0;
  for (int i = 0; i<10; ++i)
  {
    sum += i;
    v.push_back(translation3d<double>(pointxyzd(i,i,i)));
  }
  // multiply all the translations together
  translation3d<double> t = std::accumulate(v.begin(), v.end(),
                                            translation3d<double>(), 
                                            std::multiplies<translation3d<double> >());
  CPPUNIT_ASSERT(pointxyzd(sum, sum, sum) == t*pointxyzd());
}

void TestTranslation3D::testInverse()
{
  translation3d<double> t0(pointxyzd(1., 2., 3.));
  CPPUNIT_ASSERT(t0.inverse() == translation3d<double>(pointxyzd(-1., -2., -3.)));
}
void TestTranslation3D::testInvert()
{
  translation3d<double> t0(pointxyzd(1., 2., 3.));
  t0.invert();
  CPPUNIT_ASSERT(t0 == translation3d<double>(pointxyzd(-1., -2., -3.)));
}

