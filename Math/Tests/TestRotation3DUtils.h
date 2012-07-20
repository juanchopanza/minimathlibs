//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_TESTROTATION3DUTILS_H__
#define TESTS_TESTROTATION3DUTILS_H__

#include "Math/Point3D.h"
#include "Math/Matrix.h"
#include "Math/MatrixOps.h"
#include "Math/Rotation3D.h"
#include "Math/Transform3D.h"
#include "Defines.h"

namespace TestUtils
{

// generate a random Rotation3D
inline Math::Rotation3D randomRotation()
{
  const double divX = 1 + (std::rand()%8);
  const double divY = 1 + (std::rand()%8);
  const double divZ = 1 + (std::rand()%8);
  return Math::Rotation3DZYX(PI/divZ, PI/divY, PI/divX);
}

// generate a random point
inline Math::PointXYZD randomPoint(unsigned int range, 
                                   double centre = 0.)
{
  double x = centre + std::rand()%range;
  double y = centre + std::rand()%range;
  double z = centre + std::rand()%range;
  return Math::PointXYZD(x,y,z);
}

// generate a random translation
inline Math::Translation3D randomTranslation(unsigned int range, 
                                             double centre = 0)
{
  return Math::Translation3D(randomPoint(range, centre));
}

template <typename R>
bool isInverse(const R& rot, const R& rotInv)
{
  PointXYZD ref(111.,222.,333.);
  PointXYZD pTest = rot*ref;
  pTest = rotInv*pTest;
  bool test = Math::equal(pTest, ref, 500);
  if (!test) 
  {
    std::cout << "\ntestInverse p: " << ref
              << "\n p1: " << pTest << "\n";
  }
  return test;
}

bool isInverse(const AxisAngle& rot, const AxisAngle& rotInv)
{
  return isInverse(Rotation3D(rot), Rotation3D(rotInv));
}


template <typename R>
bool testInverse()
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    R rot(PI/i);
    bool test = true;
    R rotInv(rot.inverse(test));
    test = test && isInverse(rot, rotInv);
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
    bool test = true;
    rotInv.invert(test);
    test = test && isInverse(rot, rotInv);
    if (!test) return false;
  }
  return true;
}

template <typename R2>
bool testInverseRotation3D()
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    Rotation3D rot(R2(PI/i));
    bool test = true;
    Rotation3D rotInv(rot.inverse(test));
    test = test &&isInverse(rot, rotInv);
    if (!test) return false;
  }
  return true;
}

template <typename R2>
bool testInvertRotation3D()
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    Rotation3D rot(R2(PI/i));
    Rotation3D rotInv = rot;
    bool test = true;
    rotInv.invert(test);
    test = test && isInverse(rot, rotInv);
    if (!test) return false;
  }
  return true;
}

bool testInverseAxisAngle(const Math::PointXYZD& axis)
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    AxisAngle rot(axis, PI/i);
    bool test = true;
    AxisAngle rotInv(rot.inverse(test));
    test = test &&isInverse(rot, rotInv);
    if (!test) return false;
  }
  return true;
}

bool testInvertAxisAngle(const Math::PointXYZD& axis)
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    AxisAngle rot(axis, PI/i);
    AxisAngle rotInv = rot;
    bool test = true;
    rotInv.invert(test);
    test = test && isInverse(rot, rotInv);
    if (!test) return false;
  }
  return true;
}


template <typename R2>
bool testInverseRotation3DZYX()
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    Rotation3DZYX rot(R2(PI/i));
    bool test = true;
    Rotation3DZYX rotInv(rot.inverse(test));
    test = test &&isInverse(rot, rotInv);
    if (!test) return false;
  }
  return true;
}

template <typename R2>
bool testInvertRotation3DZYX()
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    Rotation3DZYX rot(R2(PI/i));
    Rotation3DZYX rotInv = rot;
    bool test = true;
    rotInv.invert(test);
    test = test && isInverse(rot, rotInv);
    if (!test) return false;
  }
  return true;
}


template <typename R>
bool testInverseTransform3D()
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    Math::Transform3D trans(R(PI/i), Math::Translation3D(111,222,333));
    bool test = true;
    Math::Transform3D transInv(trans.inverse(test));
    test = test && isInverse(trans, transInv);
    if (!test) return false;
  }

  for (unsigned int i = 1; i<9; ++i) 
  {
    Math::Transform3D trans(Math::Translation3D(111,222,333), R(PI/i));
    bool test = true;
    Math::Transform3D transInv(trans.inverse(test));
    test = test && isInverse(trans, transInv);
    if (!test) return false;
  }
  return true;
}

template <typename R>
bool testInvertTransform3D()
{
  for (unsigned int i = 1; i<9; ++i) 
  {
    Math::Transform3D trans(R(PI/i), Math::Translation3D(111, 222, 333));
    Math::Transform3D transInv = trans;
    bool test = true;
    transInv.invert(test);
    test = test && isInverse(trans, transInv);
    if (!test) return false;
  }

  for (unsigned int i = 1; i<9; ++i) 
  {
    Math::Transform3D trans(Math::Translation3D(111,222,333), R(PI/i));
    Math::Transform3D transInv = trans;
    bool test;
    transInv.invert(test);
    test = test && isInverse(trans, transInv);
    if (!test) return false;
  }

  return true;
}

template <typename R>
void testFindTransformationAxisRot()
{
  for (int i = 1; i<9; ++i)
  {
    Math::Rotation3D rot = R(PI/i);
    Math::Matrix<double,3> orig;
    Math::setColumn(orig, p100, 0);
    Math::setColumn(orig, p010, 1);
    Math::setColumn(orig, p111, 2);
    Math::Matrix<double,3> prime = rot*orig;
    bool success = true;

    Math::Matrix<double,3> rot2 = Math::transformation(orig, prime, success);
    CPPUNIT_ASSERT_MESSAGE("Inversion failed", success);
    CPPUNIT_ASSERT(rot.equal(rot2, 1));
  }
}


} // namespace TestUtils

#endif
