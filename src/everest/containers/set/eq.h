#pragma once

#include <everest/containers/set.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class T>
class Set;

template<class T>
class Eq<Set<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Set<T>& lhs, const Set<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}