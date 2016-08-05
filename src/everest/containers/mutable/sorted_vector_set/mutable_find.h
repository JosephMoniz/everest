#pragma once

#include <everest/containers/mutable/mutable_sorted_vector_set.h>
#include <everest/traits/unlawful/mutable/mutable_find.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template <class T>
class MutableFind<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static T* FindInPlace(const T& item, MutableSortedVectorSet<T>& set) noexcept {
    return set.FindInPlace(item);
  }

};

}