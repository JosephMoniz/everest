#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_set.h>
#include <everest/traits/unlawful/findable.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template <class T>
class Findable<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Find(const T& item, MutableSortedVectorSet<T>& set) noexcept {
    return set.Find(item);
  }

};

}