#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_set.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template <class T>
class Containable<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& item, const MutableSortedVectorSet<T>& set) noexcept {
    return set.Contains(item);
  }

};

}