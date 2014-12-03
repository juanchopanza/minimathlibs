//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the BSD 2-Clause License 
// - see < http://opensource.org/licenses/BSD-2-Clause>
//


#ifndef MATH_TYPE_TRAITS_HPP_
#define MATH_TYPE_TRAITS_HPP_

#include <tr1/type_traits>

namespace Math
{
template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> { typedef T type; };

using std::tr1::is_arithmetic;
using std::tr1::integral_constant;
using std::tr1::is_class;

} // Math

/// adapted from wikibooks.org example
/// http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Member_Detector
///
#define MINIMATHLIBS_HAS_MEMBER_(X)                                                       \
template<typename T, class Enable = void>                                    \
struct has_member_##X                                                        \
{                                                                            \
    static const bool value = false;                                         \
};                                                                           \
                                                                             \
template<typename T>                                                         \
class has_member_##X<T, typename enable_if<is_class<T>::value>::type>        \
{                                                                            \
    struct fallback { int X; };                                              \
    struct derived : T, fallback { };                                        \
                                                                             \
    template<typename U, U> struct check;                                    \
                                                                             \
    typedef char yes[1];                                                     \
    typedef char no[2];                                                      \
                                                                             \
    template<typename U> static yes & func(check<int fallback::*, &U::X> *); \
    template<typename U> static no & func(...);                              \
  public:                                                                    \
    typedef has_member_##X type;                                             \
    static const bool value = sizeof(func<derived>(0)) == 2;                 \
}



#define MINIMATHLIBS_HAS_TYPEDEF_(member)                                      \
template <typename T>                                             \
struct has_typedef_##member                                       \
{                                                                 \
    typedef char yes[1];                                          \
    typedef char no[2];                                           \
    template <typename C>  static yes& test(typename C::member*); \
    template <typename> static no& test(...);                     \
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);  \
}


namespace Math
{

MINIMATHLIBS_HAS_MEMBER_(x);
MINIMATHLIBS_HAS_MEMBER_(y);
MINIMATHLIBS_HAS_MEMBER_(z);

template <typename T>
struct is_point3d : integral_constant<bool, 
                                      has_member_x<T>::value &&
                                      has_member_y<T>::value &&
                                      has_member_z<T>::value > {};

MINIMATHLIBS_HAS_MEMBER_(normalize);

}

#endif
