#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_set.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template <class T>
class Container<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const MutableSortedVectorSet<T>& set) noexcept {
    return set.Length();
  }

  static bool IsEmpty(const MutableSortedVectorSet<T>& set) noexcept {
    return set.IsEmpty();
  }

};

}