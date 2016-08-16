#pragma once

#include <utility>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/unlawful/one.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/bounded.h>
#include <everest/strings/string.h>

namespace everest {

template<class T>
class AverageMonoid final {

  T _sum;

  T _count;

public:

  AverageMonoid(const T& value) noexcept : _sum(value),
                                           _count(OneVal<T>::One()) { }

  AverageMonoid(T&& value) noexcept : _sum(std::move(value)),
                                      _count(OneVal<T>::One()) { }

  AverageMonoid(const T& sum, const T& count) noexcept : _sum(sum),
                                                         _count(count) { }

  const T& Value() const noexcept {
    return (_count > ZeroVal<T>::Zero())
      ? _sum / _count
      : ZeroVal<T>::Zero();
  }

  AverageMonoid<T> Add(const AverageMonoid<T>& other) const noexcept {
    return AverageMonoid<T>(_sum + other._sum, _count + other._count);
  }

  bool Equals(const AverageMonoid<T>& other) const noexcept {
    return Value() == other.Value();
  }

  Ordering Compare(const AverageMonoid<T>& other) const noexcept {
    return Ord<T>::Compare(Value(), other.Value());
  }

  const AverageMonoid<T>& Min(const AverageMonoid<T>& other) const noexcept {
    return (Compare(other) == Ordering::GREATER)
      ? other
      : *this;
  }

  const AverageMonoid<T>& Max(const AverageMonoid<T>& other) const noexcept {
    return (Compare(other) == Ordering::LESS)
      ? other
      : *this;
  }

  String Show() const noexcept {
    return String("AverageMonoid(") + Shows<T>::Show(Value()) + String(")");
  }

  static AverageMonoid<T> Zero() {
    return AverageMonoid<T>(ZeroVal<T>::Zero());
  }

};

template<class T>
class Eq<AverageMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const AverageMonoid<T>& lhs, const AverageMonoid<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

template<class T>
class Monoid<AverageMonoid<T>> final {
public:

  static constexpr bool exists = true;

};

template<class T>
class Ord<AverageMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const AverageMonoid<T>& lhs, const AverageMonoid<T>& rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static const AverageMonoid<T>& Min(const AverageMonoid<T>& lhs, const AverageMonoid<T>& rhs) noexcept {
    return lhs.Min(rhs);
  }

  static const AverageMonoid<T>& Max(const AverageMonoid<T>& lhs, const AverageMonoid<T>& rhs) noexcept {
    return lhs.Max(rhs);
  }

};

template<class T>
class Semigroup<AverageMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static AverageMonoid<T> Add(const AverageMonoid<T>& lhs, const AverageMonoid<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

template<class T>
class Shows<AverageMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const AverageMonoid<T>& monoid) noexcept {
    return monoid.Show();
  }

};

template<class T>
class ZeroVal<AverageMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static AverageMonoid<T> Zero() {
    return AverageMonoid<T>::Zero();
  }

};

}
