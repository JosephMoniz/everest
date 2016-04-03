#pragma once

#include <everest/types/string.h>
#include <everest/containers/monoids/min_monoid.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T>
class Shows<MinMonoid<T>> {
public:

  static constexpr bool exists = true;

  static String Show(const MinMonoid<T>& monoid) noexcept {
    return String("MinMonoid(") + Shows<T>::Show(monoid) + String(")");
  }

};

}