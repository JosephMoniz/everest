#pragma once

#include <everest/monoids/min_monoid.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/unlawful/bounded.h>

namespace everest {

template<class T>
class MinMonoid;

template <class T>
class ZeroVal<MinMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static MinMonoid<T> Zero() {
    return MinMonoid<T>(Bounded<T>::MaxValue());
  }

};

}