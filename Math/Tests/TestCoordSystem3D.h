//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//

#ifndef TESTS_COORDSYSTEM3D_H__
#define TESTS_COORDSYSTEM3D_H__


#include <iostream>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/CoordSystem3D.h"
#include "Math/Point3DOps.h"

class TestCoordSystem3D : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(TestCoordSystem3D);
  CPPUNIT_TEST(testInstantiation);
  CPPUNIT_TEST(testCopyConstruction);
  CPPUNIT_TEST(testAssignment);
  CPPUNIT_TEST(testEquality);
  CPPUNIT_TEST(testInequality);
  CPPUNIT_TEST(testComponents);
  CPPUNIT_TEST_SUITE_END();

 protected:

  typedef Math::CoordSystemXYZ<double> CoordsXYZ;

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
    CPPUNIT_ASSERT( 1 == c1.x() );
    CPPUNIT_ASSERT( 2 == c1.y() );
    CPPUNIT_ASSERT( 3 == c1.z() );
  }


};


#endif
