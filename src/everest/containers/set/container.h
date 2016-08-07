#pragma once

#include <everest/containers/set.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template <class T>
class Set;

template <class T>
class Container<Set<T>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const Set<T>& set) noexcept {
    return set.Length();
  }

  static bool IsEmpty(const Set<T>& set) noexcept {
    return set.IsEmpty();
  }

};

}