#pragma once

#include <stddef.h>
#include <cstdint>
#include <everest/types/int8.h>
#include <everest/memory/memory.h>
#include <everest/containers/option.h>
#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/droppable.h>
#include <everest/traits/unlawful/stack.h>
#include <everest/traits/unlawful/queue.h>

namespace everest {

template<class T>
class Vector final {

  size_t _length;

  Memory<T> _memory;

public:

  Vector() noexcept : _memory(Memory<T>()) { }

  Vector(std::initializer_list<T> list) noexcept {
    auto memory  = MutableMemory<T>(list.size());
    auto pointer = memory.MutablePointer();
    auto offset  = 0;
    for (auto it = list.begin(); it != list.end(); it++) {
      pointer[offset++] = *it;
    }
    _length = list.size();
    _memory = memory;
  }

  Vector(const T* src, size_t length) noexcept {
    auto memory  = MutableMemory<T>(length);
    auto pointer = memory.MutablePointer();
    for (auto i = 0; i < length; i++) {
      src[i] = pointer[i];
    }
    _length = length;
    _memory = memory;
  }

  Vector(Memory<T>&& memory) noexcept : _length(memory.Length()),
                                        _memory(std::move(memory)) { }

  Vector(MutableVector<T>&& vector) noexcept : _length(vector.Length()),
                                               _memory(std::move(vector._memory)) { }

  Vector(MutableVector<T>&& vector, size_t length) noexcept : _length(length),
                                                              _memory(std::move(vector._memory)) { }

  Vector(Vector<T>&& vector, size_t length) noexcept : _length(length),
                                                       _memory(std::move(vector._memory)) { }

  size_t Length() const noexcept {
    return _length;
  }

  const T* Pointer() const noexcept {
    return _memory.Pointer();
  }

  Option<const T&> At(size_t offset) const noexcept {
    if (offset < _length) {
      return Some(_memory.Pointer()[offset]);
    } else {
      return None<const T&>();
    }
  }

};

template <class T>
class Containable<Vector<T>, T> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& n, const Vector<T>& vector) noexcept {
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (size_t i = 0; i < length; i++) {
      if (pointer[i] == n) {
        return true;
      }
    }
    return false;
  }

};

template <class T>
class Container<Vector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const Vector<T>& vector) noexcept {
    return vector.Length();
  }

  static constexpr bool IsEmpty(const Vector<T>& vector) noexcept {
    return vector.Length() == 0;
  }

};

template<class T>
class Eq<Vector<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const Vector<T>& lhs, const Vector<T>& rhs) noexcept {
    auto leftLength = lhs.Length();
    if (leftLength == rhs.Length()) {
      auto lhsPointer = lhs.Pointer();
      auto rhsPointer = rhs.Pointer();
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
class Foldable<Vector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const Vector<T>& vector) noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (size_t i = 0; i < length; i++) {
      memo = Semigroup<T>::Add(memo, pointer[i]);
    }
    return memo;
  }

  template <class Fn,
            class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const Vector<T>& vector) noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (size_t i = 0; i < length; i++) {
      memo = Semigroup<T>::Add(memo, f(pointer[i]));
    }
    return memo;
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const Vector<T>& vector) noexcept
  {
    auto memo    = init;
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
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
                           const Vector<T>& vector) noexcept
  {
    auto memo    = init;
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (size_t i = 0; i < length; i++) {
      memo = f(memo, pointer[i]);
    }
    return memo;
  }

};

template<class T>
class Functor<Vector<T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static Vector<B> Map(F f, const Vector<T>& vector) noexcept {
    auto length = vector.Length();
    auto memory = MutableMemory<B>(length);
    auto source = vector.Pointer();
    auto dest   = memory.MutablePointer();
    for (size_t i = 0; i < length; i++) {
      dest[i] = f(source[i]);
    }
    return Vector<T>(Memory<T>(memory));
  }

};

template<class T>
class Monad<Vector<T>> {
public:

  static constexpr bool exists = true;

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr Vector<B> FlatMap(F f, const Vector<T>& vector) noexcept {
    auto results = MutableVector<T>();
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (auto i = 0; i < length; i++) {
      auto expanded = f(pointer[i]);
      auto ePointer = expanded.Pointer();
      auto eLength  = expanded.Length();
      for (auto j = 0; j < eLength; j++) {
        results.Push(ePointer[j]);
      }
    }
    return Vector<T>(std::move(results));
  }

  template <class B>
  static constexpr Vector<B> Then(const Vector<T>& first, const Vector<B>& second) noexcept {
    return second;
  }

};

template <class T>
class Hashable<Vector<T>> {
public:

  static constexpr bool exists = true;

  static int Hash(const Vector<T>& vector) noexcept {
    int result   = 37;
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (size_t i = 0; i < length; i++) {
      result = 37 * result + Hash(pointer[i]);
    }
    return result;
  }

};

template<class T>
class Monoid<Vector<T>> {
public:
  static constexpr bool exists = true;
};

template<class T>
class Ord<Vector<T>> {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const Vector<T> &lhs, const Vector<T> &rhs) noexcept {
    auto lhsLength = lhs.Length();
    auto rhsLength = rhs.Length();
    if (rhsLength == lhsLength) {
      auto lhsPointer = lhs.Pointer();
      auto rhsPointer = rhs.Pointer();
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

  static constexpr const Vector<T>& Min(const Vector<T> &lhs,
                                        const Vector<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const Vector<T>& Max(const Vector<T> &lhs,
                                        const Vector<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

template<class T>
class Semigroup<Vector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Vector<T> Add(const Vector<T>& lhs, const Vector<T>& rhs) noexcept {
    auto lhsLength   = lhs.Length();
    auto rhsLength   = rhs.Length();
    auto memory      = MutableMemory<T>(lhsLength + rhsLength);
    auto destPointer = memory.MutablePointer();
    auto lhsPointer  = lhs.Pointer();
    auto rhsPointer  = rhs.Pointer();
    for (size_t i = 0; i < lhsLength; i++) {
      destPointer[i] = lhsPointer[i];
    }
    for (size_t i = 0; i < rhsLength; i++) {
      destPointer[i + lhsLength] = rhsPointer[i];
    }
    return Vector<T>(Memory<T>(memory));
  }

};

template <class T>
class Shows<Vector<T>> {
public:

  static constexpr bool exists = true;

  static const String Show(const Vector<T>& vector) noexcept {
    auto out     = String("Vector(");
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (size_t i = 0; i < length; i ++) {
      out = out + Shows<T>::Show(pointer[i]) + String(", ");
    }
    return Take(out.Length() - 2, out) + String(")");
  }

};

template<class T>
class Hexable<Vector<T>> {
public:

  static constexpr bool exists = true;

  static String ToHex(const Vector<T>& value) noexcept {
    return ToHexFromBigEndianBytePointer((unsigned char*) &value, value.Length());
  }

};

template<class T>
class ZeroVal<Vector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Vector<T> Zero() noexcept {
    return Vector<T>(Memory<T>());
  }

};

template <class T>
class Takeable<Vector<T>> {
public:

  static constexpr bool exists = true;

  static Vector<T> Take(size_t length, const Vector<T>& vector) noexcept {
    return Vector<T>(Memory<T>(vector.Pointer(), Min(length, vector.Length())));
  }

  template<class Predicate>
  static Vector<T> TakeWhile(Predicate predicate, const Vector<T>& vector) noexcept {
    size_t offset = 0;
    size_t length = vector.Length();
    auto pointer  = vector.Pointer();
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    return Vector<T>(Memory<T>(pointer, offset));
  }

};

template <class T>
class Droppable<Vector<T>> {
public:

  static constexpr bool exists = true;

  static Vector<T> Drop(size_t length, const Vector<T>& vector) noexcept {
    auto vectorLength = vector.Length();
    auto offset       = Min(length, length);
    return Vector<T>(Memory<T>(vector.Pointer()[offset], vectorLength - offset));
  }

  template<class Predicate>
  static Vector<T> DropWhile(Predicate predicate, const Vector<T>& vector) noexcept {
    size_t offset = 0;
    size_t length = vector.Length();
    auto pointer  = vector.Pointer();
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    return Vector<T>(Memory<T>(pointer[offset], length - offset));
  }

};

template <class T>
struct Stack<Vector<T>> {
public:

  static constexpr bool exists = true;

  static Vector<T> Push(const T& item, const Vector<T>& vector) noexcept {
    auto capacity = vector.Length() + 1;
    auto memory   = MutableMemory<T>(vector.Pointer(), capacity);
    memory.MutablePointer()[capacity] = item;
    return Vector<T>(Memory<T>(memory));
  }

  static Vector<T> Pop(const Vector<T>& vector) noexcept {
    return Vector<T>(Memory<T>(vector.Pointer(), Max(vector.Length() - 1, 0)));
  }

  static Option<const T&> Top(const Vector<T>& vector) noexcept {
    auto length = vector.Length();
    if (length > 0) {
      return Some(vector.Pointer()[length - 1]);
    } else {
      return None<const T&>();
    }
  }

};

template <class T>
class Queue<Vector<T>> {
public:

  static constexpr bool exists = true;

  static Vector<T> Enqueue(const T& item, const Vector<T>& vector) noexcept {
    auto capacity = vector.Length() + 1;
    auto memory   = MutableMemory<T>(vector.Pointer(), capacity);
    memory.MutablePointer()[capacity] = item;
    return Vector<T>(Memory<T>(memory));
  }

  static Vector<T> Dequeue(const Vector<T>& vector) noexcept {
    if (vector.Length() > 0) {
      return Vector<T>(Memory<T>(vector.Pointer()[1], vector.Length() - 1));
    } else {
      return Vector<T>();
    }
  }

  static Option<const T&> Front(const Vector<T>& vector) noexcept {
    return vector.At(0);
  }

};

template <class T>
class Filterable<Vector<T>> {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static Vector<T> Filter(Predicate predicate, const Vector<T>& vector) noexcept {
    auto results = MutableVector<T>();
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (auto i = 0; i < length; i++) {
      if (predicate(pointer[i])) {
        results.Push(pointer[i]);
      }
    }
    return Vector<T>(std::move(results));
  }

};

}
