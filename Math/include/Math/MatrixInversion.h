//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//


#ifndef MATH_MATRIXINVERSION_H__
#define MATH_MATRIXINVERSION_H__


//
// functor to invert a matrix. The idea is that we specialize this for
// the types of matrices that we can invert, and leave the rest unimplemented.
//
// @author Juan Palacios juan.palacios.puyana@gmail.com
//

namespace Math {

namespace detail {

template <typename T, unsigned int N1, unsigned int N2>
class MatrixInvertor;

template <typename T>
class MatrixInvertor<T, 1, 1> {
 public:
  template <typename M>
  bool operator()(M& mat) const 
  {
    typedef typename M::value_type value_type;
    if (mat(0,0) == value_type()) return false;
    mat(0.0) = value_type(1)/mat(0,0);
  }
};

template <typename T>
class MatrixInvertor<T, 2, 2> {
 public:
  template <typename M>
  bool operator()(M& mat) const
  {
    typedef typename M::value_type value_type;
    value_type det = mat(0,0)*mat(1,1) - mat(0,1)*mat(1,0);
    if (det == value_type()) return false;
    std::swap(mat(0,0), mat(1,1)); 
    mat(0,1)*=-1;
    mat(1,0) *= -1;
    mat /= det;
    return true; 
  }

};

template <typename T>
class MatrixInvertor<T, 3, 3> {
 public:
  template <typename M>
  bool operator()(M& mat) const 
  {

    typedef typename M::value_type value_type;
    value_type a = mat(1,1)*mat(2,2) - mat(1,2)*mat(2,1); // ek -fh
    value_type b = mat(1,2)*mat(2,0) - mat(2,2)*mat(1,0); // fg - kd
    value_type c = mat(1,0)*mat(2,1) - mat(1,1)*mat(2,0); // dh - eg

    value_type det = a*mat(0,0) + b*mat(0,1) + c*mat(0,2);

    if (det == value_type()) return false;

    value_type d = mat(0,2)*mat(2,1) - mat(0,1)*mat(2,2); // ch - bk
    value_type e = mat(0,0)*mat(2,2) - mat(0,2)*mat(2,0); // ak - cg
    value_type f = mat(2,0)*mat(0,1) - mat(0,0)*mat(2,1); // gb - ah

    value_type g = mat(0,1)*mat(1,2) - mat(0,2)*mat(1,1); // bf - ce
    value_type h = mat(0,2)*mat(1,0) - mat(0,0)*mat(1,2); // cd - af
    value_type k = mat(0,0)*mat(1,1) - mat(0,1)*mat(1,0); // ae - bd

    mat(0,0) = a;
    mat(1,0) = b;
    mat(2,0) = c;
    mat(0,1) = d;
    mat(1,1) = e;
    mat(2,1) = f;
    mat(0,2) = g;
    mat(1,2) = h;
    mat(2,2) = k;

    mat /= det;

    return true;
  }

};

} // detail
} // Math

#endif
