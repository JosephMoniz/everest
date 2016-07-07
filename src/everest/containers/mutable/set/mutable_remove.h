#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/unlawful/mutable/mutable_remove.h>

namespace everest {

template<class T>
class MutableSet;

template<class T>
class MutableRemove<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static MutableSet<T>& RemoveInPlace(const T& item, MutableSet<T>& set) noexcept {
    auto bucket = set.GetAllocatedBucket(item);
    set.RedactBucketSize(bucket);
    FilterInPlace(NotEquals(item), *bucket);
    set.AddBucketSize(bucket);
    return set;
  }

  template<class U, class = std::enable_if<Iteration<U>::exists>>
  static MutableSet<T>& RemoveInPlace(const U& source, MutableSet<T>& set) noexcept {
    ForEach(source, [&](const T& item) {
      RemoveInPlace(item, set);
    });
  }

};

}