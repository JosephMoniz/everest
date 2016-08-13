#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class T>
class MutableSet;

template<class T>
class Eq<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableSet<T>& lhs, const MutableSet<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}