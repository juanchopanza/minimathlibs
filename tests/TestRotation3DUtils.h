//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_TESTROTATION3DUTILS_H_
#define TESTS_TESTROTATION3DUTILS_H_

#include "minimath/point3d.hpp"
#include "minimath/matrix.hpp"
#include "minimath/matrix_ops.hpp"
#include "minimath/rotation3d.hpp"
#include "minimath/transform3d.hpp"
#include "Defines.h"

namespace TestUtils
{

using namespace minimath;

// generate a random Rotation3D
inline rotation3d<double> randomRotation()
{
  const double divX = 1 + (std::rand()%8);
  const double divY = 1 + (std::rand()%8);
  const double divZ = 1 + (std::rand()%8);
  return rotation3dzyx<double>(PI/divZ, PI/divY, PI/divX);
}

// generate a random point
inline pointxyzd randomPoint(unsigned int range, 
                                   double centre = 0.)
{
  double x = centre + std::rand()%range;
  double y = centre + std::rand()%range;
  double z = centre + std::rand()%range;
  return pointxyzd(x,y,z);
}

// generate a random translation
inline translation3d<double> randomTranslation(unsigned int range, 
                                             double centre = 0)
{
  return translation3d<double>(randomPoint(range, centre));
}

template <typename R>
bool isInverse(const R& rot, const R& rotInv)
{
  pointxyzd ref(111.,222.,333.);
  pointxyzd pTest = rot*ref;
  pTest = rotInv*pTest;
  bool test = equal(pTest, ref, 750);
  if (!test) 
  {
    std::cout << "\ntestInverse p: " << ref
              << "\n p1: " << pTest << "\n";
  }
  return test;
}

template <typename T>
bool isInverse(const axisangle<T>& rot, const axisangle<T>& rotInv)
{
  return isInverse(rotation3d<T>(rot), rotation3d<T>(rotInv));
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
    rotation3d<double> rot(R2(PI/i));
    bool test = true;
    rotation3d<double> rotInv(rot.inverse(test));
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
    rotation3d<double> rot(R2(PI/i));
    rotation3d<double> rotInv = rot;
    bool test = true;
    rotInv.invert(test);
    test = test && isInverse(rot, rotInv);
    if (!test) return false;
  }
  return true;
}

inline bool testInverseAxisAngle(const pointxyzd& axis)
{
  typedef pointxyzd::scalar_type scalar_type;
  for (unsigned int i = 1; i<9; ++i) 
  {
    axisangle<scalar_type> rot(axis, PI/i);
    bool test = true;
    axisangle<scalar_type> rotInv(rot.inverse(test));
    test = test &&isInverse(rot, rotInv);
    if (!test) return false;
  }
  return true;
}

inline bool testInvertAxisAngle(const pointxyzd& axis)
{
  typedef pointxyzd::scalar_type scalar_type;
  for (unsigned int i = 1; i<9; ++i) 
  {
    axisangle<scalar_type> rot(axis, PI/i);
    axisangle<scalar_type> rotInv = rot;
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
    rotation3dzyx<double> rot(R2(PI/i));
    bool test = true;
    rotation3dzyx<double> rotInv(rot.inverse(test));
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
    rotation3dzyx<double> rot(R2(PI/i));
    rotation3dzyx<double> rotInv = rot;
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
    transform3d<double> trans(rotation3d<double>(R(PI/i)), translation3d<double>(111,222,333));
    bool test = true;
    transform3d<double> transInv(trans.inverse(test));
    test = test && isInverse(trans, transInv);
    if (!test) return false;
  }

  for (unsigned int i = 1; i<9; ++i) 
  {
    transform3d<double> trans(translation3d<double>(111,222,333),
                              rotation3d<double>(R(PI/i)));
    bool test = true;
    transform3d<double> transInv(trans.inverse(test));
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
    transform3d<double> trans(rotation3d<double>(R(PI/i)), 
                              translation3d<double>(111, 222, 333));
    transform3d<double> transInv = trans;
    bool test = true;
    transInv.invert(test);
    test = test && isInverse(trans, transInv);
    if (!test) return false;
  }

  for (unsigned int i = 1; i<9; ++i) 
  {
    transform3d<double> trans(translation3d<double>(111,222,333), 
                              rotation3d<double>(R(PI/i)));
    transform3d<double> transInv = trans;
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
  double a100[] = {1., 0., 0.};
  double a010[] = {0., 1., 0.};
  double a111[] = {1., 1., 1.};

  for (int i = 1; i<9; ++i)
  {
    rotation3d<double> rot = R(PI/i);
    matrix<double,3> orig;
    setColumn(orig, a100, 0);
    setColumn(orig, a010, 1);
    setColumn(orig, a111, 2);
    matrix<double,3> prime = rot*orig;
    bool success = true;

    matrix<double,3> rot2 = transformation(orig, prime, success);
    CPPUNIT_ASSERT_MESSAGE("Inversion failed", success);
    CPPUNIT_ASSERT(rot.equal(rot2, 1));
  }
}


} // namespace TestUtils

#endif
