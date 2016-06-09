#pragma once

#include <everest/memory/mutable_memory.h>
#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>
#include <everest/traits/unlawful/mutable/mutable_remove.h>
#include <everest/traits/unlawful/mutable/mutable_add.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template<class T>
class MutableSet final {

  friend class Container<MutableSet<T>>;
  friend class MutableAdd<MutableSet<T>>;
  friend class Containable<MutableSet<T>, T>;
  friend class MutableRemove<MutableSet<T>>;
  friend class Iteration<MutableSet<T>>;
  friend class MutableFilter<MutableSet<T>>;

  MutableMemory<MutableVector<T>> _memory;

  size_t _size;

  MutableVector<T>* GetBucket(const T& item) noexcept {
    auto hash    = Hash(item) % Length(_memory);
    auto pointer = MutablePointable<MutableMemory<MutableVector<T>>>::Pointer(_memory);
    return &pointer[hash];
  }

  const MutableVector<T>* GetConstBucket(const T& item) const noexcept {
    auto hash    = Hash(item) % Length(_memory);
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

template <class T>
class Containable<MutableSet<T>, T> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& item, const MutableSet<T>& set) noexcept {
    return Containable<MutableVector<T>, T>::Contains(item, *set.GetConstBucket(item));
  }

};

template <class T>
class Container<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const MutableSet<T>& set) noexcept {
    return set._size;
  }

  static constexpr bool IsEmpty(const MutableSet<T>& set) noexcept {
    return set._size == 0;
  }

};

template <class T>
class Filterable<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static MutableSet<T> Filter(Predicate predicate, const MutableSet<T>& set) noexcept {
    auto results = MutableSet<T>();
    ForEach(set, [&](const T& item) {
      if (predicate(item)) {
        PushInPlace(item, results);
      }
    });
    return results;
  }

};

template<class T>
class Functor<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static MutableSet<B> Map(F f, const MutableSet<T>& set) noexcept {
    auto result = MutableSet<B>();
    ForEach(set, [&](const T& item) {
      PushInPlace(f(item), result);
    });
    return result;
  }

};

template <class T>
class Hashable<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  static int Hash(const MutableSet<T>& set) noexcept {
    int result = 37;
    ForEach(set, [&](const T& item) {
      result = 37 * result + Hashable<T>::Hash(item);
    });
    return result;
  }

};

template<class T>
class Monad<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr MutableSet<B> FlatMap(F f, const MutableSet<T>& set) noexcept {
    auto results = MutableSet<T>();
    ForEach(set, [&](const T& item) {
      ForEach(f(item), [&](const T& inner) {
        PushInPlace(inner, results);
      });
    });
    return results;
  }

  template <class B>
  static constexpr MutableSet<B> Then(const MutableSet<T>& first, const MutableSet<B>& second) noexcept {
    return second;
  }

};

template<class T>
class Monoid<MutableSet<T>> {
public:
  static constexpr bool exists = true;
};

template <class T>
class MutableFilter<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static MutableSet<T>& FilterInPlace(Predicate predicate, MutableSet<T>& set) noexcept {
    auto memorySize    = Length(set._memory);
    auto memoryPointer = Pointer(set._memory);
    for (size_t i = 0; i < memorySize; i++) {
      FilterInPlace(predicate, memoryPointer[i]);
    }
    return set;
  }

};

template<class T>
class Semigroup<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  static constexpr MutableSet<T> Add(const MutableSet<T>& lhs, const MutableSet<T>& rhs) noexcept {
    auto results = MutableSet<T>();
    ForEach(lhs, [&](const T& item) {
      PushInPlace(item, results);
    });
    ForEach(rhs, [&](const T& item) {
      PushInPlace(item, results);
    });
    return results;
  }

};

template <class T>
class Shows<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  static const String Show(const MutableSet<T>& vector) noexcept {
    auto out = String("MutableSet(");
    ForEach(vector, [&](const T& item) {
      out = out + Shows<T>::Show(item) + String(", ");
    });
    return Take(Length(out) - 2, out) + String(")");
  }

};

template<class T>
class ZeroVal<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  static constexpr MutableSet<T> Zero() noexcept {
    return MutableSet<T>();
  }

};

template <class T>
class Iteration<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableSet <T>& container, const F& function) noexcept {
    auto memorySize    = Length(container._memory);
    auto memoryPointer = Pointer(container._memory);
    for (size_t i = 0; i < memorySize; i++) {
      ForEach(memoryPointer[i], [&](const T& item) {
        function(item);
      });
    }
  }

};

template <class T>
class MutableRemove<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  static MutableSet<T>& RemoveInPlace(const T& item, MutableSet<T>& set) noexcept {
    auto bucket = set.GetAllocatedBucket(item);
    set.RedactBucketSize(bucket);
    FilterInPlace(NotEquals(item), *bucket);
    set.AddBucketSize(bucket);
    return set;
  }

  static MutableSet<T>& RemoveInPlace(const MutableSet<T>& source, MutableSet<T>& set) noexcept {
    ForEach(set, [&](const T& item) {
      RemoveInPlace(item, set);
    });
  }

};

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
