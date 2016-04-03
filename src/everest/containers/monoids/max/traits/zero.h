#pragma once

#include <everest/containers/monoids/max_monoid.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/unlawful/bounded.h>

namespace everest {

template <class T>
class ZeroVal<MaxMonoid<T>> {
public:

  static constexpr bool exists = true;

  static constexpr MaxMonoid<T> Zero() {
    return Bounded<MaxMonoid<T>>::MinValue();
  }

};

}