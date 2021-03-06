#pragma once

#include <everest/strings/string.h>
#include <everest/monoids/max_monoid.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T>
class MaxMonoid;

template<class T>
class Shows<MaxMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const MaxMonoid<T>& monoid) noexcept {
    return monoid.Show();
  }

};

}