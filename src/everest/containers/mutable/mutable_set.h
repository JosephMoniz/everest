#pragma once

#include <everest/memory/mutable_memory.h>
#include <everest/containers/mutable/mutable_vector.h>

namespace everest {

template<class T>
class MutableSet final {

  MutableMemory<MutableVector<T>> _memory;

  size_t _size;

  template <class U>
  MutableVector<T>* GetBucket(const U& item) noexcept {
    auto hash    = Hashable<U>::Hash(item).Value() % _memory.Length();
    auto pointer = _memory.MutablePointer();
    return &pointer[hash];
  }

  template <class U>
  const MutableVector<T>* GetConstBucket(const U& item) const noexcept {
    auto hash    = Hashable<U>::Hash(item).Value() % _memory.Length();
    auto pointer = _memory.Pointer();
    return &pointer[hash];
  }

  template <class U>
  MutableVector<T>* GetAllocatedBucket(const U& item) noexcept {
    auto bucket = GetBucket(item);
    if (bucket != nullptr && *bucket == nullptr) { bucket->Reserve(4); }
    return bucket;
  }

  void RedactBucketSize(const MutableVector<T>* bucket) noexcept {
    _size -= bucket->Length();
  }

  void AddBucketSize(const MutableVector<T>* bucket) noexcept {
    _size += bucket->Length();
  }

  MutableSet<T>& ResizeIfNecessary() noexcept {
    if (_size == _memory.Length()) {
      auto old  = std::move(_memory);
      _memory   = MutableMemory<MutableVector<T>>(old.Length() * 2);
      _size     = 0;
      MovingForEach([&](T&& item) {
        AddInPlace(std::move(item));
      });
      return *this;
    }
  }

public:

  MutableSet() : _memory(128),
                 _size(0) { }

  template <class U>
  MutableSet(U&& element) noexcept : _memory(128),
                                     _size(0)
  {
    AddInPlace(std::move(element));
  }

  template <class U, class... U2>
  MutableSet(U&& element, U2&&... elements) noexcept : _memory(128),
                                                       _size(0)
  {
    AddInPlace(std::move(element), std::move(elements)...);
  };

  MutableSet(const MutableSet<T>& other) = delete;

  MutableSet(MutableSet<T>&& other) noexcept : _memory(std::move(other._memory)),
                                               _size(other._size)
  {
    other._size = 0;
  }

  MutableSet<T>& operator=(const MutableSet<T>& other) = delete;

  MutableSet<T>& operator=(MutableSet<T>&& other) noexcept {
    _memory     = std::move(other._memory);
    _size       = other._size;
    other._size = 0;
    return *this;
  }

  bool Contains(const T& item) const noexcept {
    return GetConstBucket(item)->Contains(item);
  }

  template <class U>
  T* FindInPlace(const U& item) noexcept {
    return GetBucket(item)->FindInPlace(item);
  }

  template <class U>
  const T* Find(const U& item) const noexcept {
    return GetConstBucket(item)->Find(item);
  }

  size_t Length() const noexcept {
    return _size;
  }

  bool IsEmpty() const noexcept {
    return _size == 0;
  }

  template <class F>
  void ForEach(F function) const noexcept {
    auto memorySize                       = _memory.Length();
    const MutableVector<T>* memoryPointer = _memory.Pointer();
    for (size_t i = 0; i < memorySize; i++) {
      memoryPointer[i].ForEach(function);
    }
  }

  template <class F>
  void MovingForEach(F function) noexcept {
    auto memorySize                 = _memory.Length();
    MutableVector<T>* memoryPointer = _memory.MutablePointer();
    for (size_t i = 0; i < memorySize; i++) {
      memoryPointer[i].MovingForEach(function);
    }
  }

  template <class Predicate>
  bool Any(Predicate predicate) const noexcept {
    auto memorySize                       = _memory.Length();
    const MutableVector<T>* memoryPointer = _memory.Pointer();
    for (size_t i = 0; i < memorySize; i++) {
      if (memoryPointer[i].Any(predicate)) {
        return true;
      }
    }
    return false;
  }

  MutableSet<T> Copy() const noexcept {
    auto copy = MutableSet<T>();
    ForEach([&](const T& item) {
      copy.AddInPlace(Copyable<T>::Copy(item));
    });
    return copy;
  }

  bool Equals(const MutableSet<T>& rhs) const noexcept {
    if (_size == rhs.Length()) {
      auto buckets = _memory.Pointer();
      for (size_t i = 0; i < _size; i++) {
        auto bucketLength  = buckets[i].Length();
        auto bucketPointer = buckets[i].Pointer();
        for (size_t j = 0; j < bucketLength; j++) {
          if (!rhs.Contains(bucketPointer[j])) {
            return false;
          }
        }
      }
      return true;
    } else {
      return false;
    }
  }

  template<class Predicate>
  MutableSet<T> Filter(Predicate predicate) const noexcept {
    auto results = MutableSet<T>();
    ForEach([&](const T& item) {
      if (predicate(item)) {
        results.AddInPlace(item);
      }
    });
    return results;
  }

  template <class F, class B = typename std::result_of<F(T)>::type>
  MutableSet<B> Map(F f) const noexcept {
    auto result = MutableSet<B>();
    ForEach([&](const T& item) {
      result.AddInPlace(f(item));
    });
    return result;
  }

  HashValue Hash() const noexcept {
    unsigned int result = 37;
    ForEach([&](const T& item) {
      result = 37 * result + Hashable<T>::Hash(item).Value();
    });
    return HashValue(result);
  }

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  MutableSet<B> FlatMap(F f) const noexcept {
    auto results = MutableSet<T>();
    ForEach([&](const T& item) {
      f(item).ForEach([&](const T& inner) {
        results.AddInPlace(inner);
      });
    });
    return results;
  }

  template <class B>
  MutableSet<B> Then(const MutableSet<B>& second) const noexcept {
    return second;
  }

  MutableSet<T>& AddInPlace(const T& source) noexcept {
    auto bucket = GetAllocatedBucket(source);
    RedactBucketSize(bucket);
    bucket->FilterInPlace(NotEquals(source));
    bucket->PushInPlace(source);
    AddBucketSize(bucket);
    return ResizeIfNecessary();
  }

  MutableSet<T>& AddInPlace(T&& source) noexcept {
    auto bucket = GetAllocatedBucket(source);
    RedactBucketSize(bucket);
    bucket->FilterInPlace(NotEquals(source));
    bucket->PushInPlace(std::move(source));
    AddBucketSize(bucket);
    return ResizeIfNecessary();
  }

  template <class... T2>
  MutableSet<T>& AddInPlace(T&& source, T2&&... sources) noexcept {
    AddInPlace(std::move(source));
    AddInPlace(std::move(sources)...);
  }

  MutableSet<T>& AddInPlace(const MutableSet<T>& source) noexcept {
    source.ForEach([&](const T& item) {
      AddInPlace(item);
    });
    return *this;
  }

  MutableSet<T>& AddInPlace(MutableSet<T>&& source) noexcept {
    ForEach(source, [&](T&& item) {
      AddInPlace(std::move(item));
    });
    return *this;
  }

  template<class Predicate>
  MutableSet<T>& FilterInPlace(Predicate predicate) noexcept {
    auto memorySize    = _memory.Length();
    auto memoryPointer = _memory.MutablePointer();
    for (size_t i = 0; i < memorySize; i++) {
      RedactBucketSize(&memoryPointer[i]);
      memoryPointer[i].FilterInPlace(predicate);
      AddBucketSize(&memoryPointer[i]);
    }
    return *this;
  }

  MutableSet<T>& RemoveInPlace(const T& item) noexcept {
    auto bucket = GetAllocatedBucket(item);
    RedactBucketSize(bucket);
    bucket->FilterInPlace(NotEquals(item));
    AddBucketSize(bucket);
    return *this;
  }

  template <class U, class = typename std::enable_if<Iteration<U>::exists>::type>
  MutableSet<T>& RemoveInPlace(const U& source) noexcept {
    source.ForEach([&](const T& item) {
      RemoveInPlace(item);
    });
  }

  template <class U>
  MutableSet<T>& RemoveSimilarInPlace(const U& item) noexcept {
    auto bucket = GetAllocatedBucket(item);
    RedactBucketSize(bucket);
    bucket->FilterInPlace([&](const T& entry) {
      return entry != item;
    });
    AddBucketSize(bucket);
    return *this;
  }

  MutableSet<T> Add(const MutableSet<T>& rhs) const noexcept {
    auto results = MutableSet<T>();
    ForEach([&](const T& item) {
      results.AddInPlace(item);
    });
    rhs.ForEach([&](const T& item) {
      results.AddInPlace(item);
    });
    return results;
  }

  String Show() const noexcept {
    auto out = String("MutableSet(");
    ForEach([&](const T& item) {
      out = std::move(out) + Shows<T>::Show(item) + String(", ");
    });
    return Takeable<String>::Take(out.Length() - 2, std::move(out)) + String(")");
  }

  MutableSet<T> Subtract(const MutableSet<T>& rhs) const noexcept {
    auto results = MutableSet<T>();
    ForEach([&](const T& item) {
      results.AddInPlace(item);
    });
    rhs.ForEach([&](const T& item) {
      results.RemoveInPlace(item);
    });
    return results;
  }

  static MutableSet<T> Zero() noexcept {
    return MutableSet<T>();
  }

};

}