//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MATH_TYPE_TRAITS_HPP_
#define MATH_TYPE_TRAITS_HPP_

#include <tr1/type_traits>

#define HAS_MEMBER_(member) \
template <typename T> \
struct has_##member \
{ \
    typedef char yes[1]; \
    typedef char no[2];  \
    template <std::size_t N> struct chk_; \
    template <typename C>  static yes& test(chk_<sizeof(&C::member)>*); \
    template <typename> static no& test(...); \
    static const bool value = sizeof(test<T>(0)) == sizeof(yes); \
}


namespace Math
{
template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> { typedef T type; };

using std::tr1::is_arithmetic;
using std::tr1::integral_constant;

HAS_MEMBER_(x);
HAS_MEMBER_(y);
HAS_MEMBER_(z);

template <typename T>
struct is_point3d : integral_constant<bool, 
                                      has_x<T>::value && has_y<T>::value && has_z<T>::value > {};

HAS_MEMBER_(normalize);

}

#endif
