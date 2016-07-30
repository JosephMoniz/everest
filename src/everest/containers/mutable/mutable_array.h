#pragma once

#include <initializer_list>
#include <everest/traits/lawful/functor.h>

namespace everest {

template<class T, size_t S>
class MutableArray final {

  friend class Functor<MutableArray<T, S>>;

  T _array[S];

public:

  MutableArray() { }

  MutableArray(std::initializer_list<T> list) {
    size_t i = 0;
    auto it  = list.begin();
    for (; it != list.end(); it++, i++) {
      _array[i] = *it;
    }
  }

  MutableArray(const T* pointer, size_t length) noexcept {
    for (size_t i = 0; i < length; i++) {
      _array[i] = pointer[i];
    }
  }

  const T* Pointer() const noexcept {
    return (const T*) &_array;
  };

  T* MutablePointer() const noexcept {
    return (T*) &_array;
  };

  template <class F>
  void ForEach(const F& function) const noexcept {
    for (size_t i = 0; i < S; i++) {
      function(_array[i]);
    }
  }

  String Show() const noexcept {
    auto out = String("MutableArray(");
    ForEach([&](const T& item) {
      out = std::move(out) + Shows<T>::Show(item) + String(", ");
    });
    return Take(out.Length() - 2, std::move(out)) + String(")");
  }

  bool Equals(const MutableArray<T, S>& other) const noexcept {
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
  bool Equals(const MutableArray<T, Rs>& other) const noexcept {
    return false;
  }

  Ordering Compare(const MutableArray<T, S> &other) const noexcept {
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
  Ordering Compare(const MutableArray<T, Rs> &other) const noexcept {
    return (S > Rs)
      ? Ordering::GREATER
      : Ordering::LESS;
  }

  const MutableArray<T, S>& Min(const MutableArray<T, S> &other) const noexcept {
    return (Compare(other) == Ordering::GREATER)
      ? other
      : *this;
  }

  const MutableArray<T, S>& Max(const MutableArray<T, S> &other) const noexcept {
    return (Compare(other) == Ordering::LESS)
      ? other
      : *this;
  }

  template <class F, class B = typename std::result_of<F(T)>::type>
  MutableArray<B, S> Map(F f) const noexcept {
    auto newArray = MutableArray<B, S>();
    auto pointer  = Pointer();
    for (size_t i = 0; i < S; i++) {
      newArray._array[i] = f(pointer[i]);
    }
    return newArray;
  }

  size_t Length() const noexcept {
    return (size_t) S;
  }

  bool IsEmpty() const noexcept {
    return S == 0;
  }

  bool Contains(const T& n) const noexcept {
    auto pointer = Pointer();
    for (size_t i = 0; i < S; i++) {
      if (pointer[i] == n) {
        return true;
      }
    }
    return false;
  }

  template <size_t Rs, size_t Ns = S + Rs>
  MutableArray<T, S + Rs> Add(const MutableArray<T, Rs>& rhs) const noexcept {
    auto newArray   = MutableArray<T, Ns>();
    auto lhsPointer = Pointer();
    auto rhsPointer = rhs.Pointer();
    auto newPointer = newArray.MutablePointer();
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
      result = 37 * result + Hashable<T>::Hash(pointer[i]);
    }
    return HashValue(result);
  }

  T Fold() const noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = Pointer();
    for (size_t i = 0; i < S; i++) {
      memo = Semigroup<T>::Add(memo, pointer[i]);
    }
    return memo;
  }

  template <class Fn,
    class M = typename std::result_of<Fn(T)>::type>
  M FoldMap(Fn f) const noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = Pointer();
    for (size_t i = 0; i < S; i++) {
      memo = Semigroup<T>::Add(memo, f(pointer[i]));
    }
    return memo;
  }

  template <class Fn, class B>
  B FoldR(const B& init, Fn f) const noexcept {
    auto memo    = init;
    auto pointer = Pointer();
    for (size_t i = S - 1; i != 0; i--) {
      memo = f(memo, pointer[i]);
    }
    if (S > 0) {
      memo = f(memo, pointer[0]);
    }
    return memo;
  }

  template <class Fn, class B>
  B FoldL(const B& init, Fn f) const noexcept {
    auto memo    = init;
    auto pointer = Pointer();
    for (size_t i = 0; i < S; i++) {
      memo = f(memo, pointer[i]);
    }
    return memo;
  }

  static MutableArray<T, S> Zero() noexcept {
    return MutableArray<T, S>({});
  }

};

}