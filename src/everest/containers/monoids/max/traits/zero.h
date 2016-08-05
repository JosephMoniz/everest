#pragma once

#include <everest/containers/monoids/max_monoid.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/unlawful/bounded.h>

namespace everest {

template<class T>
class MaxMonoid;

template <class T>
class ZeroVal<MaxMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static MaxMonoid<T> Zero() {
    return MaxMonoid<T>(Bounded<T>::MinValue());
  }

};

}