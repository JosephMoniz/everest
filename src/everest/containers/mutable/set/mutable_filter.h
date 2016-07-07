#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_filter.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class MutableFilter<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static MutableSet<T>& FilterInPlace(Predicate predicate, MutableSet<T>& set) noexcept {
    auto memorySize    = Length(set._memory);
    auto memoryPointer = MutablePointer(set._memory);
    for (size_t i = 0; i < memorySize; i++) {
      set.RedactBucketSize(&memoryPointer[i]);
      MutableFilter<MutableVector<T>>::FilterInPlace(predicate, memoryPointer[i]);
      set.AddBucketSize(&memoryPointer[i]);
    }
    return set;
  }

};

}