//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#include <iostream>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/CoordSystem3D.h"
#include "Math/Point3DOps.h"
#include "Math/Utils.h"

#include <limits>
#include <cmath>

#include "TestCoordSystem3D.h"

void Setup()
{
  EPS = std::numeric_limits<CoordsXYZ::value_type>::epsilon();
}

void TestCoordSystem3D::testInstantiation()
{
  CoordsXYZ c1;
  CoordsXYZ c2(1,2,3);
}

void TestCoordSystem3D::testEquality()
{
  CPPUNIT_ASSERT(Math::equal(CoordsXYZ(), CoordsXYZ()));
  CoordsXYZ c1(1, 2, 3);
  CoordsXYZ c2(1,2,3);
  CPPUNIT_ASSERT( Math::equal(c1, c2));
}

void TestCoordSystem3D::testInequality()
{
  CoordsXYZ c1(10, 20, 30);
  CoordsXYZ c2(1,2,3);
  CPPUNIT_ASSERT( !Math::equal(c1, c2));
}

void TestCoordSystem3D::testCopyConstruction() 
{
  CoordsXYZ c1(1,2,3);
  CoordsXYZ c2 = c1;
  CPPUNIT_ASSERT( Math::equal(c1, c2));
}

void TestCoordSystem3D::testAssignment()  {
  CoordsXYZ c1(1,2,3);
  CoordsXYZ c2;
  c2 = c1;
  CPPUNIT_ASSERT( Math::equal(c1, c2));
}

void TestCoordSystem3D::testComponents()  {
  CoordsXYZ c1(1,2,3);
  CPPUNIT_ASSERT( Math::compareWithTolerance(1., c1.x(), EPS) );
  CPPUNIT_ASSERT( Math::compareWithTolerance(2., c1.y(), EPS) );
  CPPUNIT_ASSERT( Math::compareWithTolerance(3., c1.z(), EPS) );
}

void TestCoordSystem3D::testAccessX()
{
  CoordsXYZ c(10, 20, 30);
  CPPUNIT_ASSERT( Math::compareWithTolerance(c.x(), 10., EPS));
}

void TestCoordSystem3D::testAccessY()
{
  CoordsXYZ c(10, 20, 30);
  CPPUNIT_ASSERT( Math::compareWithTolerance(c.y(), 20., EPS));
}

void TestCoordSystem3D::testAccessZ()
{
  CoordsXYZ c(10, 20, 30);
  CPPUNIT_ASSERT( Math::compareWithTolerance(c.z(), 30., EPS));
}

void TestCoordSystem3D::testSetX()
{
  CoordsXYZ c;
  c.x(3.14);
  CPPUNIT_ASSERT(  Math::compareWithTolerance(c.x(), 3.14, EPS) );
}

void TestCoordSystem3D::testSetY()
{
  CoordsXYZ c;
  c.y(3.14);
  CPPUNIT_ASSERT(  Math::compareWithTolerance(c.y(), 3.14, EPS) );
}


void TestCoordSystem3D::testSetZ()
{
  CoordsXYZ c;
  c.z(3.14);
  CPPUNIT_ASSERT(  Math::compareWithTolerance(c.z(), 3.14, EPS) );
}

void TestCoordSystem3D::testPlusEquals()
{
  CoordsXYZ pd(1, 2, 3);
  pd += CoordsXYZ(10,20,30);
  CPPUNIT_ASSERT( equal(pd,CoordsXYZ(11,22,33), 1));
}

void TestCoordSystem3D::testMinusEquals()
{
  CoordsXYZ pd(11, 22, 33);
  pd -= CoordsXYZ(10,20,30);
  CPPUNIT_ASSERT( equal(pd, CoordsXYZ(1,2,3), 1));
}

void TestCoordSystem3D::testTimesEqualsScalar()
{
  CoordsXYZ pd(1, 2, 3);
  pd *= 11;
  CPPUNIT_ASSERT( equal(pd, CoordsXYZ(11,22,33),1));

}

void TestCoordSystem3D::testDivideEqualsScalar()
{
  CoordsXYZ pd(100, 200, 300);
  pd /= 10;
  CPPUNIT_ASSERT( equal(pd, CoordsXYZ(10,20,30), 1) );
}

