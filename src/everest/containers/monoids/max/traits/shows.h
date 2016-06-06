#pragma once

#include <everest/types/string.h>
#include <everest/containers/monoids/max_monoid.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T>
class MaxMonoid;

template<class T>
class Shows<MaxMonoid<T>> {
public:

  static constexpr bool exists = true;

  static String Show(const MaxMonoid<T>& monoid) noexcept {
    return String("MaxMonoid(") + Shows<T>::Show(monoid.Value()) + String(")");
  }

};

}