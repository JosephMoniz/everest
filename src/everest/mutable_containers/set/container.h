#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class Container<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const MutableSet<T>& set) noexcept {
    return set.Length();
  }

  static bool IsEmpty(const MutableSet<T>& set) noexcept {
    return set.IsEmpty();
  }

};

}