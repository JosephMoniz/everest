#pragma once

#include <everest/containers/set.h>
#include <everest/traits/unlawful/subtract.h>

namespace everest {

template <class T>
class Set;

template<class T>
class Subtractable<Set<T>> final {
public:

  static constexpr bool exists = true;

  static Set<T> Subtract(const Set<T>& lhs, const Set<T>& rhs) noexcept {
    return lhs.Subtract(rhs);
  }

};

}