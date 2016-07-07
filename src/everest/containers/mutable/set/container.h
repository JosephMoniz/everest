#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class Container<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const MutableSet<T>& set) noexcept {
    return set._size;
  }

  static constexpr bool IsEmpty(const MutableSet<T>& set) noexcept {
    return set._size == 0;
  }

};

}