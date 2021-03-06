#pragma once

#include <stddef.h>
#include <everest/containers/option.h>
#include <everest/memory/mutable_memory.h>
#include <everest/memory/growable_memory.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/copyable.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class MutableVector final {

  friend class Vector<T>;

  size_t _length;

  GrowableMemory<T> _memory;

public:

  MutableVector() noexcept : _length(0), _memory() { }

  template <class U, class... U2>
  MutableVector(U&& element, U2&&... elements) noexcept : _length(0), _memory() {
    AddInPlace(std::move(element), std::move(elements)...);
  };

  MutableVector(GrowableMemory<T>&& memory) noexcept : _length(memory.Length()),
                                                       _memory(std::move(memory)) { }

  MutableVector(MutableMemory<T>&& memory) noexcept : _length(memory.Length()),
                                                      _memory(std::move(memory)) { }

  MutableVector(MutableMemory<T>&& memory, size_t length) noexcept : _length(length),
                                                                     _memory(std::move(memory)) { }

  MutableVector(Memory<T>&& memory) noexcept : _length(memory.Length()),
                                               _memory(std::move(memory)) { }

  MutableVector(const MutableVector<T>& other) = delete;

  MutableVector(MutableVector<T>&& other) noexcept : _length(other._length),
                                                     _memory(std::move(other._memory))
  {
    other._length = 0;
  }

  MutableVector<T>& operator=(const MutableVector<T>& other) = delete;

  MutableVector<T>& operator=(MutableVector<T>&& other) noexcept {
    _memory       = std::move(other._memory);
    _length       = other._length;
    return *this;
  }

  void Reserve(size_t size) noexcept {
    _memory.Reserve(size);
  }

  void ReserveAtLeast(size_t size) noexcept {
    _memory.ReserveAtLeast(size);
  }

  Option<const T*> At(size_t offset) const noexcept {
    auto pointer = _memory.Pointer();
    return (offset < _length && offset > 0 && pointer != nullptr)
      ? Option<const T*>::Some(&pointer[offset])
      : Option<const T*>::None();
  }

  T* AtInPlace(size_t offset) noexcept {
    auto pointer = _memory.MutablePointer();
    return (offset < _length && offset > 0 && pointer != nullptr)
      ? &pointer[offset]
      : nullptr;
  }

  template <class Predicate>
  bool Any(Predicate predicate) const noexcept {
    auto pointer  = Pointer();
    auto length   = _length;
    for (size_t i = 0; i < length; i++) {
      if (predicate(pointer[i])) {
        return true;
      }
    }
    return false;
  }

  bool Contains(const T& n) const noexcept {
    return Any([&](const T& m) { return n == m; });
  }

  size_t Length() const noexcept {
    return _length;
  }

  bool IsEmpty() const noexcept {
    return _length == 0;
  }

  const T* Pointer() const noexcept {
    return _memory.Pointer();
  }

  T* MutablePointer() noexcept {
    return _memory.MutablePointer();
  }

  template <class F>
  void ForEach(const F& function) const noexcept {
    auto bucketSize    = _length;
    auto bucketPointer = Pointer();
    for (size_t i = 0; i < bucketSize; i++) {
      function(bucketPointer[i]);
    }
  }

  template <class F>
  void MovingForEach(F function) noexcept {
    auto bucketSize    = _length;
    auto bucketPointer = _memory.MutablePointer();
    for (size_t i = 0; i < bucketSize; i++) {
      function(std::move(bucketPointer[i]));
    }
  }

  MutableVector<T> Copy() const noexcept {
    auto copy = MutableVector<T>();
    ForEach([&](const T& item) {
      copy.PushInPlace(Copyable<T>::Copy(item));
    });
    return copy;
  }

  MutableVector<T> Drop(size_t length) const noexcept {
    auto offset       = (size_t) Ord<size_t>::Min(length, _length);
    auto pointer      = Pointer();
    return MutableVector<T>(MutableMemory<T>(pointer[offset], _length - offset));
  }

  template<class Predicate>
  MutableVector<T> DropWhile(Predicate predicate) const noexcept {
    size_t offset = 0;
    auto pointer  = Pointer();
    while (offset < _length && predicate(pointer[offset])) {
      offset++;
    }
    return MutableVector<T>(MutableMemory<T>(pointer[offset], _length - offset));
  }

  bool Equals(const MutableVector<T>& rhs) const noexcept {
    if (_length == rhs.Length()) {
      auto lhsPointer = Pointer();
      auto rhsPointer = rhs.Pointer();
      for (size_t i = 0; i < _length; i++) {
        if (lhsPointer[i] != rhsPointer[i]) {
          return false;
        }
      }
      return true;
    } else {
      return false;
    }
  }

  template<class Predicate>
  MutableVector<T> Filter(Predicate predicate) const noexcept {
    auto results = MutableVector<T>();
    ForEach([&](const T& item) {
      if (predicate(item)) {
        results.PushInPlace(item);
      }
    });
    return results;
  }

  T Fold() const noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = Pointer();
    for (size_t i = 0; i < _length; i++) {
      memo = Semigroup<T>::Add(memo, pointer[i]);
    }
    return memo;
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  M FoldMap(Fn f) const noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = Pointer();
    for (size_t i = 0; i < _length; i++) {
      memo = Semigroup<T>::Add(memo, f(pointer[i]));
    }
    return memo;
  }

  template <class Fn, class B>
  B FoldR(const B& init, Fn f) const noexcept {
    auto memo    = init;
    auto pointer = Pointer();
    if (_length == 0) {
      return init;
    } else {
      for (size_t i = _length - 1; i; i--) {
        memo = f(memo, pointer[i]);
      }
      if (_length > 0) {
        memo = f(memo, pointer[0]);
      }
      return memo;
    }
  }

  template <class Fn, class B>
  B FoldL(const B& init, Fn f) const noexcept {
    auto memo    = init;
    auto pointer = Pointer();
    for (size_t i = 0; i < _length; i++) {
      memo = f(memo, pointer[i]);
    }
    return memo;
  }

  template <class F, class B = typename std::result_of<F(T)>::type>
  MutableVector<B> Map(F f) const noexcept {
    auto result = MutableVector<B>();
    result.ReserveAtLeast(_length);
    ForEach([&](const T& item) {
      result.PushInPlace(f(item));
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

  String ToHex() const noexcept {
    return ToHexFromBigEndianBytePointer((unsigned char*) Pointer(), _length);
  }

  template<class F, class B = nth_type_arg<typename std::result_of<F(T)>::type, 0>>
  MutableVector<B> FlatMap(F f) const noexcept {
    auto results = MutableVector<T>();
    ForEach([&](const T& item) {
      f(item).ForEach([&](const T& inner) {
        results.PushInPlace(inner);
      });
    });
    return results;
  }

  template <class B>
  MutableVector<B> Then(const MutableVector<B>& second) const noexcept {
    return second;
  }

  MutableVector<T>& AddInPlace(const T& source) noexcept {
    return PushInPlace(source);
  }

  MutableVector<T>& AddInPlace(T&& source) noexcept {
    return PushInPlace(std::move(source));
  }

  MutableVector<T>& AddInPlace(const MutableVector<T>& source) noexcept {
    ReserveAtLeast(_length + source.Length());
    source.ForEach([&](const T& item) {
      PushInPlace(item);
    });
    return *this;
  }

  MutableVector<T>& AddInPlace(MutableVector<T>&& source) noexcept {
    source.MovingForEach([&](T&& item) {
      PushInPlace(std::move(item));
    });
    return *this;
  }

  template <class... T2>
  MutableVector<T>& AddInPlace(T&& source, T2&&... sources) noexcept {
    AddInPlace(std::move(source));
    AddInPlace(std::move(sources)...);
  }

  MutableVector<T>& DropInPlace(size_t length) noexcept {
    auto offset       = (size_t) Ord<size_t>::Min(length, _length);
    auto pointer      = _memory.MutablePointer();
    for (auto i = 0; i + offset < _length; i++) {
      pointer[i] = pointer[i + offset];
    }
    _length -= offset;
    return *this;
  }

  template<class Predicate>
  MutableVector<T>& DropInPlaceWhile(Predicate predicate) noexcept {
    size_t offset = 0;
    size_t length = _length;
    auto pointer  = Pointer();
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    for (auto i = 0; i + offset < length; i++) {
      pointer[i] = pointer[i + offset];
    }
    _length -= offset;
    return *this;
  }

  template <class Predicate>
  MutableVector<T>& FilterInPlace(Predicate predicate) noexcept {
    size_t passed = 0;
    auto pointer  = _memory.MutablePointer();
    for (size_t i = 0; i < _length; i++) {
      if (predicate(pointer[i])) {
        if (i != passed) {
          pointer[passed] = std::move(pointer[i]);
        }
        passed++;
      }
    }
    _length = passed;
    return *this;
  }

  template <class U>
  Option<T*> FindInPlace(const U& item) noexcept {
    auto pointer = _memory.MutablePointer();
    for (size_t i = 0; i < _length; i++) {
      if (pointer[i] == item) {
        return Option<T*>::Some(&pointer[i]);
      }
    }
    return Option<T*>::None();
  }

  template <class U>
  Option<const T*> Find(const U& item) const noexcept {
    auto pointer = _memory.Pointer();
    for (size_t i = 0; i < _length; i++) {
      if (pointer[i] == item) {
        return Option<const T*>::Some(&pointer[i]);
      }
    }
    return Option<const T*>::None();
  }

  MutableVector<T>& InsertInPlace(const T& item, size_t position) noexcept {
    ReserveAtLeast(_length + 1);
    auto pointer      = _memory.MutablePointer();
    auto safePosition = (size_t) Ord<size_t>::Min(position, _length);
    for (auto i = _length; i > safePosition; i--) {
      pointer[i] = std::move(pointer[i - 1]);
    }
    pointer[safePosition] = item;
    _length++;
    return *this;
  }

  MutableVector<T>& InsertInPlace(T&& item, size_t position) noexcept {
    ReserveAtLeast(_length + 1);
    auto pointer      = _memory.MutablePointer();
    auto safePosition = (size_t) Ord<size_t>::Min(position, _length);
    for (auto i = _length; i > safePosition; i--) {
      pointer[i] = std::move(pointer[i - 1]);
    }
    pointer[safePosition] = std::move(item);
    _length++;
    return *this;
  }

  MutableVector<T>& RemoveAtInPlace(size_t position) noexcept {
    if (_length != 0 && position < _length) {
      auto newLength = _length - 1;
      auto pointer   = _memory.MutablePointer();
      for (auto i = position; i < newLength; i++) {
        pointer[i] = std::move(pointer[i + 1]);
      }
      _length = newLength;
      return *this;
    } else {
      return *this;
    }
  }

  MutableVector<T>& PushInPlace(const T& item) noexcept {
    if (_length == _memory.Length()) {
      Reserve((size_t) (_memory.Length() * 1.5));
    }
    _memory.MutablePointer()[_length++] = item;
    return *this;
  }

  MutableVector<T>& PushInPlace(T&& item) noexcept {
    if (_length == _memory.Length()) {
      Reserve((size_t) (_memory.Length() * 1.5));
    }
    _memory.MutablePointer()[_length++] = std::move(item);
    return *this;
  }

  MutableVector<T>& PopInPlace() noexcept {
    if (_length > 0) {
      _length--;
    }
    return *this;
  }

  Ordering Compare(const MutableVector<T>& other) const noexcept {
    auto otherLength = other.Length();
    if (otherLength == _length) {
      auto lhsPointer = Pointer();
      auto rhsPointer = other.Pointer();
      for (size_t i = 0; i < _length; i++) {
        switch (Ord<T>::Compare(lhsPointer[i], rhsPointer[i])) {
          case Ordering::LESS:    return Ordering::LESS;
          case Ordering::GREATER: return Ordering::GREATER;
          case Ordering::EQUAL:   continue;
        }
      }
      return Ordering::EQUAL;
    } else {
      if (_length < otherLength) {
        return Ordering::LESS;
      } else {
        return Ordering::GREATER;
      }
    }
  }

  const MutableVector<T>& Min(const MutableVector<T>& other) const noexcept {
    return (Compare(*this, other) == Ordering::GREATER)
      ? other
      : *this;
  }

  const MutableVector<T>& Max(const MutableVector<T>& other) const noexcept {
    return (Compare(*this, other) == Ordering::LESS)
      ? other
      : *this;
  }

  MutableVector<T> Enqueue(const T& item) const noexcept {
    auto capacity = _length + 1;
    auto memory   = MutableMemory<T>(Pointer(), capacity);
    memory.MutablePointer()[capacity] = item;
    return MutableVector<T>(memory);
  }

  MutableVector<T> Dequeue() const noexcept {
    if (_length > 0) {
      return MutableVector<T>(MutableMemory<T>(Pointer()[1], _length - 1));
    } else {
      return MutableVector<T>();
    }
  }

  Option<const T&> Front() const noexcept {
    return At(0);
  }

  MutableVector<T> Add(const MutableVector<T>& rhs) const noexcept {
    auto results = MutableVector<T>();
    results.ReserveAtLeast(_length + rhs.Length());
    ForEach([&](const T& item) {
      results.PushInPlace(item);
    });
    rhs.ForEach([&](const T& item) {
      results.PushInPlace(item);
    });
    return results;
  }

  String Show() const noexcept {
    return String::Builder()
      .Add("MutableVector(")
      .Add(StringJoiner(", ").Join<MutableVector<T>, T>(*this))
      .Add(")")
      .Build();
  }

  MutableVector<T> Push(const T& item) const noexcept {
    auto capacity = _length + 1;
    auto memory   = MutableMemory<T>(Pointer(), capacity);
    memory.MutablePointer()[capacity] = item;
    return MutableVector<T>(memory);
  }

  MutableVector<T> Pop() const noexcept {
    // TODO: this can have an overflow on _length = 0
    return MutableVector<T>(MutableMemory<T>(Pointer(), (size_t) Ord<size_t>::Max((_length - 1), 0)));
  }

  Option<const T&> Top() const noexcept {
    // TODO: this can have an overflow on _length = 0
    return At(_length - 1);
  }

  MutableVector<T> Take(size_t length) const noexcept {
    return MutableVector<T>(MutableMemory<T>(Pointer(), (size_t)Ord<size_t>::Min(length, _length)));
  }

  template<class Predicate>
  MutableVector<T> TakeWhile(Predicate predicate) const noexcept {
    size_t offset = 0;
    size_t length = _length;
    auto pointer  = Pointer();
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    return MutableVector<T>(MutableMemory<T>(pointer, offset));
  }

  // TODO: Make trait
  MutableVector<T>& EnqueueInPlace(const T& item) noexcept {
    PushInPlace(item);
    return *this;
  }

  // TODO: Make trait
  MutableVector<T>& EnqueueInPlace(T&& item) noexcept {
    PushInPlace(std::move(item));
    return *this;
  }

  // TODO: Make trait
  T& DequeueInPlace() noexcept {
    T result = Pointer()[0];
    DropInPlace(1);
    return result;
  }

  // TODO: Make trait
  T&& DequeueWithMove() noexcept {
    T result = std::move(MutablePointer()[0]);
    DropInPlace(1);
    return std::move(result);
  }

  static MutableVector<T> Zero() noexcept {
    return MutableVector<T>();
  }

};

}
