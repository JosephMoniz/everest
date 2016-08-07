#pragma once

#include <initializer_list>

namespace everest {

template<class T, size_t S>
class Array final {
public:

  T _array[S];

  Array() noexcept { }

  // TODO: Make this move and variadic instead
  Array(std::initializer_list<T> list) noexcept {
    size_t i = 0;
    auto it  = list.begin();
    for (; it != list.end(); it++, i++) {
      _array[i] = *it;
    }
  }

  Array(const T* pointer, size_t length) noexcept {
    for (size_t i = 0; i < length; i++) {
      _array[i] = pointer[i];
    }
  }

  const T* Pointer() const noexcept {
    return (const T*) &_array;
  }

  String Show() const noexcept {
    auto out     = String("Array(");
    auto pointer = Pointer();
    for (size_t i = 0; i < S; i ++) {
      out = std::move(out) + Shows<T>::Show(pointer[i]) + String(", ");
    }
    return Take(out.Length() - 2, std::move(out)) + String(")");
  }

  bool Equals(const Array<T, S>& other) const noexcept {
    auto lhsPointer = Pointer();
    auto rhsPointer = other.Pointer();
    for (size_t i = 0; i < S; i++) {
      if (lhsPointer[i] != rhsPointer[i]) {
        return false;
      }
    }
    return true;
  }

  template<size_t Rs>
  bool Equals(const Array<T, Rs>& other) const noexcept {
    return false;
  }

  Ordering Compare(const Array<T, S>& other) const noexcept {
    auto lhsPointer = Pointer();
    auto rhsPointer = other.Pointer();
    for (size_t i = 0; i < S; i ++) {
      switch(Ord<T>::Compare(lhsPointer[i], rhsPointer[i])) {
        case Ordering::LESS:    return Ordering::LESS;
        case Ordering::GREATER: return Ordering::GREATER;
        case Ordering::EQUAL:   continue;
      }
    }
    return Ordering::EQUAL;
  }

  template<size_t Rs>
  Ordering Compare(const Array<T, Rs>& other) const noexcept {
    return (S > Rs)
      ? Ordering::GREATER
      : Ordering::LESS;
  }

  const Array<T, S>& Min(const Array<T, S>& other) const noexcept {
    return (Compare(other) == Ordering::GREATER)
      ? other
      : *this;
  }

  const Array<T, S>& Max(const Array<T, S>& other) const noexcept {
    return (Compare(other) == Ordering::LESS)
      ? other
      : *this;
  }

  template <class F, class B = typename std::result_of<F(T)>::type>
  Array<B, S> Map(F f) const noexcept {
    auto newArray = Array<B, S>();
    auto pointer  = Pointer();
    for (size_t i = 0; i < S; i++) {
      newArray._array[i] = f(pointer[i]);
    }
    return newArray;
  }

  bool Contains(const T& item) const noexcept {
    auto pointer = Pointer();
    for (size_t i = 0; i < S; i++) {
      if (pointer[i] == item) {
        return true;
      }
    }
    return false;
  }

  size_t Length() const noexcept {
    return (size_t) S;
  }

  bool IsEmpty() const noexcept {
    return S == 0;
  }

  template <size_t Rs, size_t Ns = S + Rs>
  Array<T, S + Rs> Add(const Array<T, Rs>& rhs) const noexcept {
    auto newArray   = Array<T, Ns>();
    auto lhsPointer = Pointer();
    auto rhsPointer = rhs.Pointer();
    auto newPointer = &newArray._array[0];
    for (size_t i = 0; i < S; i++) {
      newPointer[i] = lhsPointer[i];
    }
    for (size_t i = 0; i < Rs; i++) {
      newPointer[i + S] = rhsPointer[i];
    }
    return newArray;
  }

  HashValue Hash() const noexcept {
    unsigned int result = 37;
    auto pointer = Pointer();
    for (size_t i = 0; i < S; i++) {
      result = 37 * result + Hashable<T>::Hash(pointer[i]).Value();
    }
    return HashValue(result);
  }

  T Fold() const noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = Pointer();
    for (size_t i = 0; i < S; i++) {
      memo = Semigroup<T>::Add(std::move(memo), pointer[i]);
    }
    return memo;
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  M FoldMap(Fn f) const noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = Pointer();
    for (size_t i = 0; i < S; i++) {
      memo = Semigroup<T>::Add(std::move(memo), f(pointer[i]));
    }
    return memo;
  }

  template <class Fn, class B>
  B FoldR(const B& init, Fn f) const noexcept {
    auto memo    = init;
    auto pointer = Pointer();
    for (size_t i = S - 1; i; i--) {
      memo = f(std::move(memo), pointer[i]);
    }
    if (S > 0) {
      memo = f(std::move(memo), pointer[0]);
    }
    return memo;
  }

  template <class Fn, class B>
  B FoldL(const B& init, Fn f) const noexcept {
    auto memo    = init;
    auto pointer = Pointer();
    for (size_t i = 0; i < S; i++) {
      memo = f(std::move(memo), pointer[i]);
    }
    return memo;
  }

  static Array<T, S> Zero() noexcept {
    return Array<T, S>({});
  }

};

}