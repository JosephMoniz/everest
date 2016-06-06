#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/containers/mutable/mutable_bitset.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

template<class T>
class MutableSet {

  MutableMemory<MutableVector<T>> _memory;

  size_t _size;

  MutableVector<T>& GetBucket(const T& item,
                              const MutableMemory<MutableVector<T>>& memory) const noexcept
  {
    auto hash    = Hash(item) % Length(memory);
    auto pointer = MutablePointer(memory);
    return pointer[hash];
  }

  MutableVector<T>& GetAllocatedBucket(const T &item,
                                       const MutableMemory<MutableVector<T>>& memory) const noexcept
  {
    auto bucket = GetBucket(item, memory);
    if (bucket == nullptr) { bucket.Reserve(4); }
    return bucket;
  }

  size_t RedactBucketSize(size_t size, const MutableVector<T> &bucket) noexcept {
    return size - Length(bucket);
  }

  size_t AddBucketSize(size_t size, const MutableVector<T> &bucket) noexcept {
    return size + Length(bucket);
  }

  MutableSet<T>& ResizeIfNecessary() noexcept {
    if (_size == Length(_memory)) {
      auto oldMemory     = std::move(_memory);
      _memory            = MutableMemory<T>(Length(oldMemory) * 2);
      _size              = 0;
      auto memorySize    = Length(oldMemory);
      auto memoryPointer = Pointer(oldMemory);
      for (auto i = 0; i < memorySize; i++) {
        auto bucketSize    = Length(memoryPointer[i]);
        auto bucketPointer = Pointer(memoryPointer[i]);
        for (auto j = 0; j < bucketSize; j++) {
          Put(std::move(bucketPointer[j]));
        }
      }
    }
    return *this;
  }

public:

  MutableSet() : MutableSet(128) { }

  MutableSet(size_t capacity) : _memory(MutableMemory<T>(capacity)),
                                _size(0) { }

  bool Contains(const T& item) const noexcept {
    return Contains(item, GetBucket(item, _memory));
  }

  MutableSet<T>& Put(const T& item) noexcept {
    auto bucket         = GetAllocatedBucket(item, _memory);
    auto redactedSize   = RedactBucketSize(_size, bucket);
    auto filteredBucket = FilterInPlace(Equals(item), bucket);
    auto pushed         = PushInPlace(item, filteredBucket);
    _size               = AddBucketSize(redactedSize, bucket);
    return ResizeIfNecessary();
  }

  MutableSet<T>& Put(T&& item) noexcept {
    auto bucket         = GetAllocatedBucket(item, _memory);
    auto redactedSize   = RedactBucketSize(_size, bucket);
    auto filteredBucket = FilterInPlace(Equals(item), bucket);
    auto pushed         = PushInPlace(std::move(item), filteredBucket);
    _size               = AddBucketSize(redactedSize, bucket);
    return ResizeIfNecessary();
  }

  MutableSet<T>& Remove(const T& item) noexcept {
    auto bucket         = GetAllocatedBucket(item, _memory);
    auto redactedSize   = RedactBucketSize(_size, bucket);
    auto filteredBucket = FilterInPlace(Equals(item), bucket);
    _size               = AddBucketSize(redactedSize, bucket);
    return ResizeIfNecessary();
  }

};

}
