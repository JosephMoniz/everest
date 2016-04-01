#pragma once

#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/traits/lawful/semigroup.h>

namespace traitorous {

template<class T>
class GCounter {

  T _value;

public:

  GCounter(const T& number) noexcept : _value(number) { }

  GCounter<T> Increment() const noexcept {
    return GCounter(_value + OneVal<T>::One());
  }

  GCounter<T> IncrementBy(const T& number) const noexcept {
    return GCounter(_value + number);
  }

  T Value() const noexcept {
    return _value;
  }

};

template<class T>
class Shows<GCounter<T>> {
public:

  static constexpr bool exists = true;

  static String Show(const GCounter<T>& counter) noexcept {
    return String("GCounter(") + Shows<T>::Show(counter.Value()) + String(")");
  }

};

template<class T>
class Eq<GCounter<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const GCounter<T>& lhs, const GCounter<T>& rhs) noexcept {
    return lhs.Value() == rhs.Value();
  }

};

template<class T>
class ZeroVal<GCounter<T>> {
public:

  static constexpr bool exists = true;

  static constexpr GCounter<T> Zero() {
    return GCounter(Bounded<T>::MinValue());
  }

};

template<class T>
class Semigroup<GCounter<T>> {
public:

  static constexpr bool exists = true;

  static constexpr GCounter<T> Add(const GCounter<T>& lhs, const GCounter<T>& rhs) noexcept {
    return GCounter(Ord<T>::Max(lhs.Value(), rhs.Value()));
  }

};

template<class T>
class Monoid<GCounter<T>> {
public:

  static constexpr bool exists = true;

};

}