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

  friend class Semigroup<AverageMonoid<T>>;

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

};

template<class T>
class Eq<AverageMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const AverageMonoid<T>& lhs, const AverageMonoid<T>& rhs) noexcept {
    return lhs.Value() == rhs.Value();
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

  static Ordering Compare(const AverageMonoid<T> &lhs, const AverageMonoid<T> &rhs) noexcept {
    return Ord<T>::Compare(lhs.Value(), rhs.Value());
  }

  static const AverageMonoid<T>& Min(const AverageMonoid<T> &lhs, const AverageMonoid<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::GREATER)
       ? rhs
       : lhs;
  }

  static const AverageMonoid<T>& Max(const AverageMonoid<T> &lhs, const AverageMonoid<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::LESS)
       ? rhs
       : lhs;
  }

};

template<class T>
class Semigroup<AverageMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static AverageMonoid<T> Add(const AverageMonoid<T>& lhs, const AverageMonoid<T>& rhs) noexcept {
    return AverageMonoid<T>(lhs._sum + rhs._sum, lhs._count + rhs._count);
  }

};

template<class T>
class Shows<AverageMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const AverageMonoid<T>& monoid) noexcept {
    return String("AverageMonoid(") + Shows<T>::Show(monoid.Value()) + String(")");
  }

};

template<class T>
class ZeroVal<AverageMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static AverageMonoid<T> Zero() {
    return AverageMonoid<T>(Bounded<T>::MinValue());
  }

};

}
