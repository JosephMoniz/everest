#pragma once

#include <utility>

namespace everest {

template<class T>
class MinMonoid final {

  T _value;

public:

  MinMonoid(const T& value) noexcept : _value(value) { }

  MinMonoid(T&& value) noexcept : _value(std::move(value)) { }

  const T& Value() const noexcept {
    return _value;
  }

  bool Equals(const MinMonoid<T>& other) const noexcept {
    return Value() == other.Value();
  }

  Ordering Compare(const MinMonoid<T>& other) const noexcept {
    return Ord<T>::Compare(Value(), other.Value());
  }

  const MinMonoid<T>& Min(const MinMonoid<T>& other) const noexcept {
    return (Compare(other) == Ordering::GREATER)
      ? other
      : *this;
  }

  const MinMonoid<T>& Max(const MinMonoid<T>& other) const noexcept {
    return (Compare(other) == Ordering::LESS)
      ? other
      : *this;
  }

  MinMonoid<T> Add(const MinMonoid<T>& other) const noexcept {
    switch (Ord<T>::Compare(Value(), other.Value())) {
      case Ordering::LESS:    return *this;
      case Ordering::GREATER: return other;
      case Ordering::EQUAL:   return *this;
    }
  }

  String Show() const noexcept {
    return String("MinMonoid(") + Shows<T>::Show(Value()) + String(")");
  }

  static MinMonoid<T> Zero() {
    return MinMonoid<T>(Bounded<T>::MaxValue());
  }

};

}

#include <everest/monoids/min/traits/eq.h>
#include <everest/monoids/min/traits/monoid.h>
#include <everest/monoids/min/traits/ord.h>
#include <everest/monoids/min/traits/semigroup.h>
#include <everest/monoids/min/traits/shows.h>
#include <everest/monoids/min/traits/zero.h>
