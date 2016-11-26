#pragma once

#include <everest/strings/string.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/bounded.h>
#include <everest/traits/unlawful/one.h>

namespace everest {

template<class T>
class GrowOnlyCounter final {

  T _value;

public:

  GrowOnlyCounter() noexcept : _value(ZeroVal<T>::Zero()) { }

  GrowOnlyCounter(const T& number) noexcept : _value(number) { }

  GrowOnlyCounter(const GrowOnlyCounter<T>& other) noexcept : _value(other._value) { }

  GrowOnlyCounter(GrowOnlyCounter<T>&& other) noexcept : _value(std::move(other._value)) { }

  GrowOnlyCounter<T> Increment() const noexcept {
    return GrowOnlyCounter(_value + OneVal<T>::One());
  }

  GrowOnlyCounter<T> IncrementBy(const T& number) const noexcept {
    return GrowOnlyCounter(_value + number);
  }

  T Value() const noexcept {
    return _value;
  }

  GrowOnlyCounter<T> Add(const GrowOnlyCounter<T>& other) const noexcept {
    return GrowOnlyCounter(Ord<T>::Max(_value, other.Value()));
  }

  String Show() const noexcept {
    return String("GCounter(") + Shows<T>::Show(_value) + String(")");
  }

  bool Equals(const GrowOnlyCounter<T>& other) const noexcept {
    return _value == other.Value();
  }

  static GrowOnlyCounter<T> Zero() {
    return GrowOnlyCounter<T>(Bounded<T>::MinValue());
  }

};

template<class T>
class Shows<GrowOnlyCounter<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const GrowOnlyCounter<T>& counter) noexcept {
    return counter.Show();
  }

};

template<class T>
class Eq<GrowOnlyCounter<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const GrowOnlyCounter<T>& lhs, const GrowOnlyCounter<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

template<class T>
class ZeroVal<GrowOnlyCounter<T>> final {
public:

  static constexpr bool exists = true;

  static GrowOnlyCounter<T> Zero() {
    return GrowOnlyCounter<T>::Zero();
  }

};

template<class T>
class Semigroup<GrowOnlyCounter<T>> final {
public:

  static constexpr bool exists = true;

  static GrowOnlyCounter<T> Add(const GrowOnlyCounter<T>& lhs, const GrowOnlyCounter<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

template<class T>
class Monoid<GrowOnlyCounter<T>> final {
public:

  static constexpr bool exists = true;

};

}
