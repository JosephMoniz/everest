#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_set.h>
#include <everest/traits/unlawful/Pointable.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template <class T>
class Pointable<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const MutableSortedVectorSet<T>& set) noexcept {
    return set.Pointer();
  }

};

}