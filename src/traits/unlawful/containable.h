#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_CONTAINABLE
#define TRAITOROUS_TRAITS_CONTAINABLE 1

#include "containers/local_option.h"

namespace traitorous {

template <template<class> class F, class T>
struct containable {
  typedef containable<F, T> base;
public:

  static constexpr bool contains(const T& n, const F<T>& f) {
    return base::contains(n, f);
  }

  static constexpr bool exists = false;

};

template<template<class> class F, class T>
constexpr inline bool contains(const T& n, const F<T>& f) {
  return containable<F, T>::contains(n, f);
}

}

#endif

#pragma clang diagnostic pop