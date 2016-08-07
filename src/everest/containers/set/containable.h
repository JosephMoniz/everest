#pragma once

#include <everest/containers/set.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template <class T>
class Set;

template <class T>
class Containable<Set<T>> final {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& item, const Set<T>& set) noexcept {
    return set.Contains(item);
  }

};

}