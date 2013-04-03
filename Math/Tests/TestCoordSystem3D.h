//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_COORDSYSTEM3D_H_
#define TESTS_COORDSYSTEM3D_H_


#include <iostream>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/CoordSystem3D.h"
#include "Math/Point3DOps.h"
#include "Math/Utils.h"

#include <limits>
#include <cmath>


class TestCoordSystem3D : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestCoordSystem3D);
  CPPUNIT_TEST(testInstantiation);
  CPPUNIT_TEST(testCopyConstruction);
  CPPUNIT_TEST(testAssignment);
  CPPUNIT_TEST(testEquality);
  CPPUNIT_TEST(testInequality);
  CPPUNIT_TEST(testComponents);
  CPPUNIT_TEST(testAccessX);
  CPPUNIT_TEST(testAccessY);
  CPPUNIT_TEST(testAccessZ);
  CPPUNIT_TEST(testSetX);
  CPPUNIT_TEST(testSetY);
  CPPUNIT_TEST(testSetZ);
  CPPUNIT_TEST(testPlusEquals);
  CPPUNIT_TEST(testMinusEquals);
  CPPUNIT_TEST(testTimesEqualsScalar);
  CPPUNIT_TEST(testDivideEqualsScalar);

  CPPUNIT_TEST_SUITE_END();

  typedef Math::CoordSystemXYZ<double> CoordsXYZ;
  CoordsXYZ::value_type EPS; 

 public:

  void Setup()
  {
    EPS = std::numeric_limits<CoordsXYZ::value_type>::epsilon();
  }

 protected:

  void testInstantiation()
  {
    CoordsXYZ c1;
    CoordsXYZ c2(1,2,3);
  }

  void testEquality()
  {
    CPPUNIT_ASSERT(Math::equal(CoordsXYZ(), CoordsXYZ()));
    CoordsXYZ c1(1, 2, 3);
    CoordsXYZ c2(1,2,3);
    CPPUNIT_ASSERT( Math::equal(c1, c2));
  }

  void testInequality()
  {
    CoordsXYZ c1(10, 20, 30);
    CoordsXYZ c2(1,2,3);
    CPPUNIT_ASSERT( !Math::equal(c1, c2));
  }

  void testCopyConstruction() 
  {
    CoordsXYZ c1(1,2,3);
    CoordsXYZ c2 = c1;
    CPPUNIT_ASSERT( Math::equal(c1, c2));
  }
  
  void testAssignment()  {
    CoordsXYZ c1(1,2,3);
    CoordsXYZ c2;
    c2 = c1;
    CPPUNIT_ASSERT( Math::equal(c1, c2));
  }

  void testComponents()  {
    CoordsXYZ c1(1,2,3);
    CPPUNIT_ASSERT( Math::compareWithTolerance(1., c1.x(), EPS) );
    CPPUNIT_ASSERT( Math::compareWithTolerance(2., c1.y(), EPS) );
    CPPUNIT_ASSERT( Math::compareWithTolerance(3., c1.z(), EPS) );
  }

  void testAccessX()
  {
    CoordsXYZ c(10, 20, 30);
    CPPUNIT_ASSERT( Math::compareWithTolerance(c.x(), 10., EPS));
  }

  void testAccessY()
  {
    CoordsXYZ c(10, 20, 30);
    CPPUNIT_ASSERT( Math::compareWithTolerance(c.y(), 20., EPS));
  }

  void testAccessZ()
  {
    CoordsXYZ c(10, 20, 30);
    CPPUNIT_ASSERT( Math::compareWithTolerance(c.z(), 30., EPS));
  }
 
  void testSetX()
  {
    CoordsXYZ c;
    c.x(3.14);
    CPPUNIT_ASSERT(  Math::compareWithTolerance(c.x(), 3.14, EPS) );
  }

 void testSetY()
  {
    CoordsXYZ c;
    c.y(3.14);
    CPPUNIT_ASSERT(  Math::compareWithTolerance(c.y(), 3.14, EPS) );
  }


  void testSetZ()
  {
    CoordsXYZ c;
    c.z(3.14);
    CPPUNIT_ASSERT(  Math::compareWithTolerance(c.z(), 3.14, EPS) );
  }

  void testPlusEquals()
  {
    CoordsXYZ pd(1, 2, 3);
    pd += CoordsXYZ(10,20,30);
    CPPUNIT_ASSERT( equal(pd,CoordsXYZ(11,22,33), 1));
  }

  void testMinusEquals()
  {
    CoordsXYZ pd(11, 22, 33);
    pd -= CoordsXYZ(10,20,30);
    CPPUNIT_ASSERT( equal(pd, CoordsXYZ(1,2,3), 1));
  }

  void testTimesEqualsScalar()
  {
    CoordsXYZ pd(1, 2, 3);
    pd *= 11;
    CPPUNIT_ASSERT( equal(pd, CoordsXYZ(11,22,33),1));

  }

  void testDivideEqualsScalar()
  {
    CoordsXYZ pd(100, 200, 300);
    pd /= 10;
    CPPUNIT_ASSERT( equal(pd, CoordsXYZ(10,20,30), 1) );
  }


};


#endif
