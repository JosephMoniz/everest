#pragma once

#include <everest/containers/monoids/min_monoid.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/unlawful/bounded.h>

namespace everest {

template <class T>
class ZeroVal<MinMonoid<T>> {
public:

static constexpr bool exists = true;

static constexpr MinMonoid<T> Zero() {
  return Bounded<MinMonoid<T>>::MaxValue();
}

};

}