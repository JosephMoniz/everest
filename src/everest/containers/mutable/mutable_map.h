#pragma once

#include <stddef.h>
#include <everest/containers/option.h>
#include <everest/containers/mutable/map/mutable_map_entry.h>
#include <everest/containers/mutable/mutable_set.h>
#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/associative.h>
#include <everest/traits/unlawful/anyable.h>
#include <everest/traits/unlawful/copyable.h>
#include <everest/traits/unlawful/mutable/mutable_find.h>
#include <everest/traits/unlawful/mutable/mutable_associative.h>

namespace everest {

template<class K, class V>
class MutableMap final {

  friend class Containable<MutableMap<K, V>>;
  friend class Container<MutableMap<K, V>>;
  friend class MutableRemove<MutableMap<K, V>>;
  friend class Iteration<MutableMap<K, V>>;
  friend class MutableAssociative<MutableMap<K, V>>;
  friend class Eq<MutableMap<K, V>>;
  friend class Associative<MutableMap<K, V>>;

  typedef MutableVector<MutableMapEntry<K, V>> Bucket;

  MutableMemory<Bucket> _memory;

  size_t _size;

  Bucket* GetBucket(const K& key) noexcept {
    auto hash    = Hash(key) % Length(_memory);
    auto pointer = MutablePointer(_memory);
    return &pointer[hash];
  }

  const Bucket* GetConstBucket(const K& key) const noexcept {
    auto hash    = Hash(key) % Length(_memory);
    auto pointer = Pointer(_memory);
    return &pointer[hash];
  }

  Bucket* GetAllocatedBucket(const K& key) noexcept {
    auto bucket = GetBucket(key);
    if (bucket != nullptr && Length(*bucket) == 0) {
      bucket->Reserve(4);
    }
    return bucket;
  }

  void RedactBucketSize(const Bucket* bucket) noexcept {
    _size -= Length(*bucket);
  }

  void AddBucketSize(const Bucket* bucket) noexcept {
    _size += Length(*bucket);
  }

  MutableMap<K, V>& ResizeIfNecessary() noexcept {
    if (_size == Length(_memory)) {
      auto self = this;
      auto old  = std::move(_memory);
      _memory   = MutableMemory<Bucket>(Length(old) * 2);
      _size     = 0;
      ForEach(old, [&](MutableMapEntry<K, V>&& entry) {
        PutInPlace(std::move(entry.Key()), std::move(entry.Value()), *self);
      });
      return *this;
    }
  }

public:

  MutableMap() : _memory(128),
                 _size(0) { }

  MutableMap(size_t capacity) : _memory(capacity),
                                _size(0) { }

};

}

#include <everest/containers/mutable/map/traits/associative.h>
#include <everest/containers/mutable/map/traits/containable.h>
#include <everest/containers/mutable/map/traits/container.h>
#include <everest/containers/mutable/map/traits/copyable.h>
#include <everest/containers/mutable/map/traits/eq.h>
#include <everest/containers/mutable/map/traits/iteration.h>
#include <everest/containers/mutable/map/traits/mutable_associative.h>
#include <everest/containers/mutable/map/traits/mutable_remove.h>
#include <everest/containers/mutable/map/traits/semigroup.h>
#include <everest/containers/mutable/map/traits/show.h>
#include <everest/containers/mutable/map/traits/zero.h>
