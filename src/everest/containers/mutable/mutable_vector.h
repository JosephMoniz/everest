#pragma once

#include <stddef.h>
#include <everest/containers/option.h>
#include <everest/memory/mutable_memory.h>
#include <everest/traits/unlawful/container.h>
#include <everest/traits/unlawful/containable.h>
#include <everest/traits/unlawful/filterable.h>
#include <everest/traits/unlawful/pointable.h>
#include <everest/traits/unlawful/droppable.h>
#include <everest/traits/unlawful/queue.h>
#include <everest/traits/unlawful/stack.h>
#include <everest/traits/unlawful/mutable/mutable_filter.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>
#include <everest/traits/unlawful/mutable/mutable_stack.h>
#include <everest/traits/unlawful/mutable/mutable_drop.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class MutableVector {

  friend class Vector<T>;
  friend class Container<MutableVector<T>>;
  friend class Pointable<MutableVector<T>>;
  friend class MutableFilter<MutableVector<T>>;
  friend class MutableStack<MutableVector<T>>;
  friend class MutableDrop<MutableVector<T>>;

  size_t _length;

  MutableMemory<T> _memory;

public:

  MutableVector() noexcept : _length(0), _memory() { }

  MutableVector(size_t capacity) noexcept : _length(0),
                                            _memory(MutableMemory<T>(capacity)){ }

  MutableVector(const Vector<T>& other) = delete;

  MutableVector(MutableMemory<T>&& memory) noexcept : _length(Length(memory)),
                                                      _memory(std::move(memory)) { }

  void Reserve(size_t size) noexcept {
    if (_memory == nullptr) {
      _memory = MutableMemory<T>(32);
    } else {
      if (size > Length(_memory)) {
        auto memory = MutableMemory<T>(size);
        auto dest   = MutablePointer(memory);
        auto src    = Pointer(_memory);
        for (size_t i = 0; i < _length; i++) {
          dest[i] = src[i];
        }
        _memory = std::move(memory);
      }
    }
  }

  Option<T&> Front() const noexcept {
    if (_length > 0 && _memory != nullptr) {
      return Some(Pointer(_memory)[0]);
    } else {
      return None<T&>();
    }
  }

  Option<T&> Back() const noexcept {
    if (_length > 0 && _memory != nullptr) {
      return Some(Pointer(_memory)[_length - 1]);
    } else {
      return None<T&>();
    }
  }

  Option<T&> At(size_t offset) const noexcept {
    if (offset < _length && offset > 0 && _memory != nullptr) {
      return Some(Pointer(_memory)[offset]);
    } else {
      return None<T&>();
    }
  }

};

template <class T>
class Pointable<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const MutableVector<T>& vector) noexcept {
    return (vector._memory != nullptr)
      ? Pointable<MutableMemory<T>>::Pointer(vector._memory)
      : nullptr;
  }

};

template <class T>
class Container<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const MutableVector<T>& vector) noexcept {
    return vector._length;
  }

  static constexpr bool IsEmpty(const MutableVector<T>& vector) noexcept {
    return vector._length == 0;
  }

};

template <class T>
class Containable<MutableVector<T>, T> {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& n, const MutableVector<T>& vector) noexcept {
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (size_t i = 0; i < length; i++) {
      if (pointer[i] == n) {
        return true;
      }
    }
    return false;
  }

};

template <class T>
class Droppable<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Drop(size_t length, const MutableVector<T>& vector) noexcept {
    auto vectorLength = Length(vector);
    auto offset       = Min(length, vectorLength);
    auto pointer      = Pointer(vector);
    return MutableVector<T>(MutableMemory<T>(pointer[offset], vectorLength - offset));
  }

  template<class Predicate>
  static MutableVector<T> DropWhile(Predicate predicate, const MutableVector<T>& vector) noexcept {
    size_t offset = 0;
    size_t length = Length(vector);
    auto pointer  = Pointer(vector);
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    return MutableVector<T>(MutableMemory<T>(pointer[offset], length - offset));
  }

};

template <class T>
class MutableDrop<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static MutableVector<T>& DropInPlace(size_t length, MutableVector<T>& vector) noexcept {
    auto vectorLength = Length(vector);
    auto offset       = Min(length, vectorLength);
    auto pointer      = MutablePointer(vector);
    for (auto i = 0; i + offset < vectorLength; i++) {
      pointer[i] = pointer[i + offset];
    }
    vector._length -= offset;
    return vector;
  }

  template<class Predicate>
  static MutableVector<T>& DropInPlaceWhile(Predicate predicate, MutableVector<T>& vector) noexcept {
    size_t offset = 0;
    size_t length = Length(vector);
    auto pointer  = Pointer(vector);
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    for (auto i = 0; i + offset < length; i++) {
      pointer[i] = pointer[i + offset];
    }
    vector._length -= offset;
    return vector;
  }

};

template <class T>
class Takeable<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Take(size_t length, const MutableVector<T>& vector) noexcept {
    return MutableVector<T>(MutableMemory<T>(Pointer(vector), Min(length, Length(vector))));
  }

  template<class Predicate>
  static MutableVector<T> TakeWhile(Predicate predicate, const MutableVector<T>& vector) noexcept {
    size_t offset = 0;
    size_t length = Length(vector);
    auto pointer  = Pointer(vector);
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    return MutableVector<T>(MutableMemory<T>(pointer, offset));
  }

};

template<class T>
class Eq<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableVector<T>& lhs, const MutableVector<T>& rhs) noexcept {
    auto leftLength = Length(lhs);
    if (leftLength == Length(rhs)) {
      auto lhsPointer = Pointer(lhs);
      auto rhsPointer = Pointer(rhs);
      for (size_t i = 0; i < leftLength; i++) {
        if (lhsPointer[i] != rhsPointer[i]) {
          return false;
        }
      }
      return true;
    } else {
      return false;
    }
  }

};

template <class T>
class Foldable<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const MutableVector<T>& vector) noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (size_t i = 0; i < length; i++) {
      memo = Semigroup<T>::Add(memo, pointer[i]);
    }
    return memo;
  }

  template <class Fn,
            class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const MutableVector<T>& vector) noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (size_t i = 0; i < length; i++) {
      memo = Semigroup<T>::Add(memo, f(pointer[i]));
    }
    return memo;
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const MutableVector<T>& vector) noexcept
  {
    auto memo    = init;
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (size_t i = length - 1; i; i--) {
      memo = f(memo, pointer[i]);
    }
    if (length > 0) {
      memo = f(memo, pointer[0]);
    }
    return memo;
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const MutableVector<T>& vector) noexcept
  {
    auto memo    = init;
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (size_t i = 0; i < length; i++) {
      memo = f(memo, pointer[i]);
    }
    return memo;
  }

};

template<class T>
class Functor<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static MutableVector<B> Map(F f, const MutableVector<T>& vector) noexcept {
    auto length = Length(vector);
    auto memory = MutableMemory<B>(length);
    auto source = Pointer(vector);
    auto dest   = MutablePointer(memory);
    for (size_t i = 0; i < length; i++) {
      dest[i] = f(source[i]);
    }
    return MutableVector<T>(std::move(memory));
  }

};

template<class T>
class Monad<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr MutableVector<B> FlatMap(F f, const MutableVector<T>& vector) noexcept {
    auto results = MutableVector<T>();
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (auto i = 0; i < length; i++) {
      auto expanded = f(pointer[i]);
      auto ePointer = Pointer(expanded);
      auto eLength  = Length(expanded);
      for (auto j = 0; j < eLength; j++) {
        PushInPlace(ePointer[j], results);
      }
    }
    return results;
  }

  template <class B>
  static constexpr MutableVector<B> Then(const MutableVector<T>& first, const MutableVector<B>& second) noexcept {
    return second;
  }

};

template<class T>
class Monoid<MutableVector<T>> {
public:
  static constexpr bool exists = true;
};



template<class T>
class Ord<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const MutableVector<T> &lhs, const MutableVector<T> &rhs) noexcept {
    auto lhsLength = Length(lhs);
    auto rhsLength = Length(rhs);
    if (rhsLength == lhsLength) {
      auto lhsPointer = Pointer(lhs);
      auto rhsPointer = Pointer(rhs);
      for (size_t i = 0; i < lhsLength; i++) {
        switch (Ord<T>::Compare(lhsPointer[i], rhsPointer[i])) {
          case Ordering::LESS:    return Ordering::LESS;
          case Ordering::GREATER: return Ordering::GREATER;
          case Ordering::EQUAL:   continue;
        }
      }
      return Ordering::EQUAL;
    } else {
      if (lhsLength < rhsLength) {
        return Ordering::LESS;
      } else {
        return Ordering::GREATER;
      }
    }
  }

  static constexpr const MutableVector<T>& Min(const MutableVector<T> &lhs,
                                               const MutableVector<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const MutableVector<T>& Max(const MutableVector<T> &lhs,
                                               const MutableVector<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

template <class T>
class Hashable<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static int Hash(const MutableVector<T>& vector) noexcept {
    int result   = 37;
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (size_t i = 0; i < length; i++) {
      result = 37 * result + Hash(pointer[i]);
    }
    return result;
  }

};

template<class T>
class Hexable<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static String ToHex(const MutableVector<T>& vector) noexcept {
    return ToHexFromBigEndianBytePointer((unsigned char*) &vector, Length(vector));
  }

};

template <class T>
class MutableStack<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static MutableVector<T>& PushInPlace(const T& item, MutableVector<T>& vector) noexcept {
    if (vector._memory == nullptr || vector._length == Length(vector._memory)) {
      vector.Reserve((size_t) (Length(vector._memory) * 1.5));
    }
    MutablePointer(vector._memory)[vector._length++] = item;
    return vector;
  }

  static MutableVector<T>& PushInPlace(T&& item, MutableVector<T>& vector) noexcept {
    if (vector._memory == nullptr || vector._length == Length(vector._memory)) {
      vector.Reserve((size_t) (Length(vector._memory) * 1.5));
    }
    MutablePointer(vector._memory)[vector._length++] = std::move(item);
    return vector;
  }

  static MutableVector<T>& PopInPlace(MutableVector<T>& vector) noexcept {
    if (vector._length > 0) {
      vector._length--;
    }
    return vector;
  }

};

template <class T>
class Filterable<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static MutableVector<T> Filter(Predicate predicate, const MutableVector<T>& vector) noexcept {
    auto results = MutableVector<T>();
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (auto i = 0; i < length; i++) {
      if (predicate(pointer[i])) {
        PushInPlace(pointer[i], results);
      }
    }
    return results;
  }

};

template <class T>
class MutableFilter<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static MutableVector<T>& FilterInPlace(Predicate predicate, MutableVector<T>& vector) noexcept {
    size_t passed = 0;
    auto pointer  = MutablePointer(vector._memory);
    auto length   = Length(vector);
    for (size_t i = 0; i < length; i++) {
      if (predicate(pointer[i])) {
        if (i != passed) {
          pointer[passed] = std::move(pointer[i]);
        }
        passed++;
      }
    }
    vector._length = passed;
    return vector;
  }

};

template <class T>
class Queue<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Enqueue(const T& item, const MutableVector<T>& vector) noexcept {
    auto capacity = Length(vector) + 1;
    auto memory   = MutableMemory<T>(Pointer(vector), capacity);
    MutablePointer(memory)[capacity] = item;
    return MutableVector<T>(memory);
  }

  static MutableVector<T> Dequeue(const MutableVector<T>& vector) noexcept {
    if (Length(vector) > 0) {
      return MutableVector<T>(MutableMemory<T>(Pointer(vector)[1], Length(vector) - 1));
    } else {
      return MutableVector<T>();
    }
  }

  static Option<const T&> Front(const MutableVector<T>& vector) noexcept {
    return vector.At(0);
  }

};

template<class T>
class Semigroup<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr MutableVector<T> Add(const MutableVector<T>& lhs, const MutableVector<T>& rhs) noexcept {
    auto lhsLength   = Length(lhs);
    auto rhsLength   = Length(rhs);
    auto memory      = MutableMemory<T>(lhsLength + rhsLength);
    auto destPointer = MutablePointer(memory);
    auto lhsPointer  = Pointer(lhs);
    auto rhsPointer  = Pointer(rhs);
    for (size_t i = 0; i < lhsLength; i++) {
      destPointer[i] = lhsPointer[i];
    }
    for (size_t i = 0; i < rhsLength; i++) {
      destPointer[i + lhsLength] = rhsPointer[i];
    }
    return MutableVector<T>(std::move(memory));
  }

};

template <class T>
struct Stack<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Push(const T& item, const MutableVector<T>& vector) noexcept {
    auto capacity = Length(vector) + 1;
    auto memory   = MutableMemory<T>(Pointer(vector), capacity);
    MutablePointer(memory)[capacity] = item;
    return MutableVector<T>(memory);
  }

  static MutableVector<T> Pop(const Vector<T>& vector) noexcept {
    return MutableVector<T>(MutableMemory<T>(Pointer(vector), Max(Length(vector) - 1, 0)));
  }

  static Option<const T&> Top(const Vector<T>& vector) noexcept {
    return vector.At(Length(vector) - 1);
  }

};

template <class T>
class Shows<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static const String Show(const MutableVector<T>& vector) noexcept {
    auto out     = String("MutableVector(");
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (size_t i = 0; i < length; i ++) {
      out = out + Shows<T>::Show(pointer[i]) + String(", ");
    }
    return Take(Length(out) - 2, out) + String(")");
  }

};

template<class T>
class ZeroVal<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr MutableVector<T> Zero() noexcept {
    return MutableVector<T>();
  }

};

}
