#pragma once

#include <everest/containers/set.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template <class T>
class Set;

template <class T>
class Hashable<Set<T>> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const Set<T>& set) noexcept {
    return set.Hash();
  }

};

}