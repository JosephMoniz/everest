#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/unlawful/mutable/mutable_add.h>

namespace everest {

template<class T>
class MutableSet;

template<class T>
class MutableAdd<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  static MutableSet<T>& AddInPlace(const T& source, MutableSet<T>& destination) noexcept {
    auto bucket = destination.GetAllocatedBucket(source);
    destination.RedactBucketSize(bucket);
    FilterInPlace(NotEquals(source), *bucket);
    PushInPlace(source, *bucket);
    destination.AddBucketSize(bucket);
    return destination.ResizeIfNecessary();
  }

  static MutableSet<T>& AddInPlace(T&& source, MutableSet<T>& destination) noexcept {
    auto bucket = destination.GetAllocatedBucket(source);
    destination.RedactBucketSize(bucket);
    FilterInPlace(NotEquals(source), *bucket);
    PushInPlace(std::move(source), *bucket);
    destination.AddBucketSize(bucket);
    return destination.ResizeIfNecessary();
  }

  static MutableSet<T>& AddInPlace(const MutableSet<T>& source, MutableSet<T>& destination) noexcept {
    ForEach(source, [&](const T& item) {
      AddInPlace(item, destination);
    });
    return destination;
  }

  static MutableSet<T>& AddInPlace(MutableSet<T>&& source, MutableSet<T>& destination) noexcept {
    ForEach(source, [&](T&& item) {
      AddInPlace(std::move(item), destination);
    });
    return destination;
  }

};

}