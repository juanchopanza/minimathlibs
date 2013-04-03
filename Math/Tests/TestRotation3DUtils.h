//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef TESTS_TESTROTATION3DUTILS_H_
#define TESTS_TESTROTATION3DUTILS_H_

#include "Math/Point3D.h"
#include "Math/Matrix.h"
#include "Math/MatrixOps.h"
#include "Math/Rotation3D.h"
#include "Math/Transform3D.h"
#include "Defines.h"

namespace TestUtils
{

using namespace Math;

// generate a random Rotation3D
inline Rotation3D<double> randomRotation()
{
  const double divX = 1 + (std::rand()%8);
  const double divY = 1 + (std::rand()%8);
  const double divZ = 1 + (std::rand()%8);
  return Rotation3DZYX<double>(PI/divZ, PI/divY, PI/divX);
}

// generate a random point
inline PointXYZD randomPoint(unsigned int range, 
                                   double centre = 0.)
{
  double x = centre + std::rand()%range;
  double y = centre + std::rand()%range;
  double z = centre + std::rand()%range;
  return PointXYZD(x,y,z);
}

// generate a random translation
inline Translation3D<double> randomTranslation(unsigned int range, 
                                             double centre = 0)
{
  return Translation3D<double>(randomPoint(range, centre));
}

template <typename R>
bool isInverse(const R& rot, const R& rotInv)
{
  PointXYZD ref(111.,222.,333.);
  PointXYZD pTest = rot*ref;
  pTest = rotInv*pTest;
  bool test = equal(pTest, ref, 500);
  if (!test) 
  {
    std::cout << "\ntestInverse p: " << ref
              << "\n p1: " << pTest << "\n";
  }
  return test;
}

template <typename T>
bool isInverse(const AxisAngle<T>& rot, const AxisAngle<T>& rotInv)
{
  return isInverse(Rotation3D<T>(rot), Rotation3D<T>(rotInv));
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
    Rotation3D<double> rot(R2(PI/i));
    bool test = true;
    Rotation3D<double> rotInv(rot.inverse(test));
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
    Rotation3D<double> rot(R2(PI/i));
    Rotation3D<double> rotInv = rot;
    bool test = true;
    rotInv.invert(test);
    test = test && isInverse(rot, rotInv);
    if (!test) return false;
  }
  return true;
}

bool testInverseAxisAngle(const PointXYZD& axis)
{
  typedef PointXYZD::scalar_type scalar_type;
  for (unsigned int i = 1; i<9; ++i) 
  {
    AxisAngle<scalar_type> rot(axis, PI/i);
    bool test = true;
    AxisAngle<scalar_type> rotInv(rot.inverse(test));
    test = test &&isInverse(rot, rotInv);
    if (!test) return false;
  }
  return true;
}

bool testInvertAxisAngle(const PointXYZD& axis)
{
  typedef PointXYZD::scalar_type scalar_type;
  for (unsigned int i = 1; i<9; ++i) 
  {
    AxisAngle<scalar_type> rot(axis, PI/i);
    AxisAngle<scalar_type> rotInv = rot;
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
    Rotation3DZYX<double> rot(R2(PI/i));
    bool test = true;
    Rotation3DZYX<double> rotInv(rot.inverse(test));
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
    Rotation3DZYX<double> rot(R2(PI/i));
    Rotation3DZYX<double> rotInv = rot;
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
    Transform3D<double> trans(Rotation3D<double>(R(PI/i)), Translation3D<double>(111,222,333));
    bool test = true;
    Transform3D<double> transInv(trans.inverse(test));
    test = test && isInverse(trans, transInv);
    if (!test) return false;
  }

  for (unsigned int i = 1; i<9; ++i) 
  {
    Transform3D<double> trans(Translation3D<double>(111,222,333),
                              Rotation3D<double>(R(PI/i)));
    bool test = true;
    Transform3D<double> transInv(trans.inverse(test));
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
    Transform3D<double> trans(Rotation3D<double>(R(PI/i)), 
                              Translation3D<double>(111, 222, 333));
    Transform3D<double> transInv = trans;
    bool test = true;
    transInv.invert(test);
    test = test && isInverse(trans, transInv);
    if (!test) return false;
  }

  for (unsigned int i = 1; i<9; ++i) 
  {
    Transform3D<double> trans(Translation3D<double>(111,222,333), 
                              Rotation3D<double>(R(PI/i)));
    Transform3D<double> transInv = trans;
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
    Rotation3D<double> rot = R(PI/i);
    Matrix<double,3> orig;
    setColumn(orig, p100, 0);
    setColumn(orig, p010, 1);
    setColumn(orig, p111, 2);
    Matrix<double,3> prime = rot*orig;
    bool success = true;

    Matrix<double,3> rot2 = transformation(orig, prime, success);
    CPPUNIT_ASSERT_MESSAGE("Inversion failed", success);
    CPPUNIT_ASSERT(rot.equal(rot2, 1));
  }
}


} // namespace TestUtils

#endif
