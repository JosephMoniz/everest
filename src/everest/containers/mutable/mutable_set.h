#pragma once

#include <everest/memory/mutable_memory.h>
#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/iteration.h>
#include <everest/traits/unlawful/copyable.h>
#include <everest/traits/unlawful/subtract.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>
#include <everest/traits/unlawful/mutable/mutable_remove.h>
#include <everest/traits/unlawful/mutable/mutable_add.h>

namespace everest {

template<class T>
class MutableSet final {

  friend class Container<MutableSet<T>>;
  friend class MutableAdd<MutableSet<T>>;
  friend class Containable<MutableSet<T>>;
  friend class MutableRemove<MutableSet<T>>;
  friend class Iteration<MutableSet<T>>;
  friend class MutableFilter<MutableSet<T>>;
  friend class Eq<MutableSet<T>>;

  MutableMemory<MutableVector<T>> _memory;

  size_t _size;

  MutableVector<T>* GetBucket(const T& item) noexcept {
    auto hash    = Hash(item).Value() % Length(_memory);
    auto pointer = MutablePointable<MutableMemory<MutableVector<T>>>::Pointer(_memory);
    return &pointer[hash];
  }

  const MutableVector<T>* GetConstBucket(const T& item) const noexcept {
    auto hash    = Hash(item).Value() % Length(_memory);
    auto pointer = Pointable<MutableMemory<MutableVector<T>>>::Pointer(_memory);
    return &pointer[hash];
  }

  MutableVector<T>* GetAllocatedBucket(const T& item) noexcept {
    auto bucket = GetBucket(item);
    if (bucket != nullptr && *bucket == nullptr) { bucket->Reserve(4); }
    return bucket;
  }

  void RedactBucketSize(const MutableVector<T>* bucket) noexcept {
    _size -= Length(*bucket);
  }

  void AddBucketSize(const MutableVector<T>* bucket) noexcept {
    _size += Length(*bucket);
  }

  MutableSet<T>& ResizeIfNecessary() noexcept {
    if (_size == Length(_memory)) {
      auto self = this;
      auto old  = std::move(_memory);
      _memory   = MutableMemory<MutableVector<T>>(Length(old) * 2);
      _size     = 0;
      ForEach(old, [&](T &&item) {
        AddInPlace(std::move(item), *self);
      });
      return *this;
    }
  }

public:

  MutableSet() : MutableSet(128) { }

  MutableSet(size_t capacity) : _memory(capacity),
                                _size(0) { }

  MutableSet(std::initializer_list<T> list) noexcept : _memory(128),
                                                       _size(0)

  {
    for (auto it = list.begin(); it != list.end(); it++) {
      AddInPlace(*it, *this);
    }
  }

  MutableSet(const MutableSet<T>& other) = delete;

  MutableSet(MutableSet<T>&& other) noexcept : _memory(std::move(other._memory)),
                                               _size(other._size)
  {
    other._size = 0;
  }

  MutableSet<T>& operator=(const MutableSet<T>& other) = delete;

  MutableSet<T>& operator=(MutableSet<T>&& other) noexcept {
    _memory       = std::move(other._memory);
    _size         = other._size;
    other._size   = 0;
    return *this;
  }

};

}

#include <everest/containers/mutable/set/containable.h>
#include <everest/containers/mutable/set/container.h>
#include <everest/containers/mutable/set/copyable.h>
#include <everest/containers/mutable/set/eq.h>
#include <everest/containers/mutable/set/filterable.h>
#include <everest/containers/mutable/set/functor.h>
#include <everest/containers/mutable/set/hashable.h>
#include <everest/containers/mutable/set/iteration.h>
#include <everest/containers/mutable/set/monad.h>
#include <everest/containers/mutable/set/monoid.h>
#include <everest/containers/mutable/set/mutable_add.h>
#include <everest/containers/mutable/set/mutable_filter.h>
#include <everest/containers/mutable/set/mutable_remove.h>
#include <everest/containers/mutable/set/semigroup.h>
#include <everest/containers/mutable/set/shows.h>
#include <everest/containers/mutable/set/subtract.h>
#include <everest/containers/mutable/set/zero.h>
