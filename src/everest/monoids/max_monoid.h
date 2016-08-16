#pragma once

#include <utility>

namespace everest {

template<class T>
class MaxMonoid final {

  T _value;

public:

  MaxMonoid(const T& value) noexcept : _value(value) { }

  MaxMonoid(T&& value) noexcept : _value(std::move(value)) { }

  const T& Value() const noexcept {
    return _value;
  }

  bool Equals(const MaxMonoid<T>& other) const noexcept {
    return Value() == other.Value();
  }

  Ordering Compare(const MaxMonoid<T>& other) const noexcept {
    return Ord<T>::Compare(Value(), other.Value());
  }

  const MaxMonoid<T>& Min(const MaxMonoid<T>& other) const noexcept {
    return (Compare(other) == Ordering::GREATER)
      ? other
      : *this;
  }

  const MaxMonoid<T>& Max(const MaxMonoid<T>& rhs) const noexcept {
    return (Compare(rhs) == Ordering::LESS)
      ? rhs
      : *this;
  }

  MaxMonoid<T> Add(const MaxMonoid<T>& other) const noexcept {
    switch (Ord<T>::Compare(Value(), other.Value())) {
      case Ordering::LESS:    return other;
      case Ordering::GREATER: return *this;
      case Ordering::EQUAL:   return *this;
    }
  }

  String Show() const noexcept {
    return String("MaxMonoid(") + Shows<T>::Show(Value()) + String(")");
  }

  static MaxMonoid<T> Zero() {
    return MaxMonoid<T>(Bounded<T>::MinValue());
  }

};

}

#include <everest/monoids/max/traits/eq.h>
#include <everest/monoids/max/traits/monoid.h>
#include <everest/monoids/max/traits/ord.h>
#include <everest/monoids/max/traits/semigroup.h>
#include <everest/monoids/max/traits/shows.h>
#include <everest/monoids/max/traits/zero.h>
