#pragma once

#include <everest/containers/mutable/mutable_sorted_vector_set.h>
#include <everest/traits/unlawful/mutable/mutable_filter.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template <class T>
class MutableFilter<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static MutableSortedVectorSet<T>& FilterInPlace(Predicate predicate, MutableSortedVectorSet<T>& set) noexcept {
    return set.FilterInPlace(predicate);
  }

};

}