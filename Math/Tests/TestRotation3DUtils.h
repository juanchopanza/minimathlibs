//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//

#ifndef TESTS_TESTROTATION3DUTILS_H__
#define TESTS_TESTROTATION3DUTILS_H__

#include "Math/Point3D.h"
#include "Defines.h"

namespace TestUtils
{

template <typename R>
bool isInverse(const R& rot, const R& rotInv)
{
  PointXYZD ref(111.,222.,333.);
  PointXYZD pTest = rot*ref;
  pTest = rotInv*pTest;
  bool test = Math::equalXYZ(pTest, ref);
  if (!test) 
  {
    std::cout << "testInverse p: " << ref
              << "\n p1: " << pTest << "\n";
  }
  return test;
}

template <typename R>
bool testInverse()
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    R rot(PI/i);
    R rotInv(rot.Inverse());
    bool test = isInverse(rot, rotInv);
    if (!test) return false;
  }
  return true;
}

template <typename R>
bool testInvert()
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    R rot(PI/i);
    R rotInv = rot;
    rotInv.Invert();
    bool test = isInverse(rot, rotInv);
    if (!test) return false;
  }
  return true;
}


} // namespace TestUtils

#endif
