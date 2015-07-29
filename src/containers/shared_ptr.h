#ifndef TRAITOROUS_CONTAINERS_SHARED_PTR_H
#define TRAITOROUS_CONTAINERS_SHARED_PTR_H

#include <memory>

#include "traits/containable.h"
#include "traits/container.h"
#include "traits/eq.h"
#include "traits/hashable.h"
#include "traits/zero.h"
#include "traits/semigroup.h"
#include "traits/monoid.h"
#include "traits/filterable.h"
#include "traits/ord.h"
#include "traits/functor.h"
#include "traits/applicative.h"
#include "traits/alternative.h"
#include "traits/monad.h"
#include "traits/monad_plus.h"
#include "traits/foldable.h"
#include "traits/unwrappable.h"

namespace traitorous {

using std::shared_ptr;

template<template <class> class F, class T>
struct containable<shared_ptr<F<T>>> {
  static constexpr bool contains(const T &n, const shared_ptr<F<T>> f) noexcept {
    return (f)
      ? containable<F<T>>::contains(n, *f)
      : false;
  }

  static constexpr bool exists = true;
};

template <template <class> class F, class T>
struct container<shared_ptr<F<T>>> {
  static constexpr size_t length(const shared_ptr<F<T>> o) noexcept {
    return (o)
      ? container<F<T>>::length(*o)
      : 0;
  }
  static constexpr bool is_empty(const shared_ptr<F<T>> o) noexcept {
    return (o)
      ? container<F<T>>::is_empty(*o)
      : true;
  }
  static constexpr bool exists = true;
};

template <template <class> class F, class T>
struct eq<shared_ptr<F<T>>> {
  static constexpr bool equals(const shared_ptr<F<T>> lhs,
                               const shared_ptr<F<T>> rhs) noexcept
  {
    return (lhs)
      ? (rhs)
        ? *lhs == *rhs
        : false
      : (rhs)
        ? false
        : true;
  }
  static constexpr bool exists = true;
};

}

#endif
