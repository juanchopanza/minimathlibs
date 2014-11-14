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

#include "Math/Translation3D.h"
#include "Math/Point3D.h"

#include "TestTranslation3D.h"

namespace
{
using namespace Math;
}

void TestTranslation3D::testInstantiation()
{
  Translation3D<double> displ1, displ2;
}

void TestTranslation3D::testDefaultEquality()
{
  CPPUNIT_ASSERT(Translation3D<double>() == Translation3D<double>());
}

void TestTranslation3D::testCopyConstruction()
{
  Translation3D<double> displ1;
  Translation3D<double> displ2(displ1);
  CPPUNIT_ASSERT(displ1==displ2);
}

void TestTranslation3D::testAssignment()
{
  Translation3D<double> displ1, displ2;
  displ2 = displ1;
  CPPUNIT_ASSERT(displ1==displ2);
}

void TestTranslation3D::testNullTranslation() {
  PointXYZD p(11, 22, 33);
  CPPUNIT_ASSERT(PointXYZD(11,22,33) == Translation3D<double>()*p);
}

void TestTranslation3D::testTranslatePoint() {
  for (int i = 0; i < 100; ++i)
  {
    PointXYZD p(11, 22, 33);
    Translation3D<double> t1(PointXYZD(i, i, i));
    CPPUNIT_ASSERT(PointXYZD(11+i, 22+i, 33+i) == t1*p);
    Translation3D<double> t2(PointXYZD(-i, -i, -i));
    CPPUNIT_ASSERT(PointXYZD(11-i, 22-i, 33-i) == t2*p);
  }
}

void TestTranslation3D::testCompoundTranslation()
{
  // make a vector of many translations
  std::vector<Translation3D<double> > v;
  int sum = 0;
  for (int i = 0; i<10; ++i)
  {
    sum += i;
    v.push_back(Translation3D<double>(PointXYZD(i,i,i)));
  }
  // multiply all the translations together
  Translation3D<double> t = std::accumulate(v.begin(), v.end(),
                                            Translation3D<double>(), 
                                            std::multiplies<Translation3D<double> >());
  CPPUNIT_ASSERT(PointXYZD(sum, sum, sum) == t*PointXYZD());
}

void TestTranslation3D::testInverse()
{
  Translation3D<double> t0(PointXYZD(1., 2., 3.));
  CPPUNIT_ASSERT(t0.inverse() == Translation3D<double>(PointXYZD(-1., -2., -3.)));
}
void TestTranslation3D::testInvert()
{
  Translation3D<double> t0(PointXYZD(1., 2., 3.));
  t0.invert();
  CPPUNIT_ASSERT(t0 == Translation3D<double>(PointXYZD(-1., -2., -3.)));
}

