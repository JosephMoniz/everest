#pragma once

#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/traits/lawful/semigroup.h>

namespace traitorous {

template<class T>
class MinMonoid {

  friend class Eq<MinMonoid<T>>;

  T _value;

public:

  MinMonoid(const T& value) noexcept : _value(value) { }

  MinMonoid(T&& value) noexcept : _value(std::move(value)) { }

  const T& Value() const noexcept {
    return _value;
  }

};

template<class T>
class Shows<MinMonoid<T>> {
public:

  static constexpr bool exists = true;

  static String Show(const MinMonoid<T>& monoid) noexcept {
    return String("MinMonoid(") + Shows<T>::Show(monoid) + String(")");
  }

};

template<class T>
class Eq<MinMonoid<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const MinMonoid<T>& lhs, const MinMonoid<T>& rhs) noexcept {
    return lhs.Value() == rhs.Value();
  }

};

template <class T>
class ZeroVal<MinMonoid<T>> {
public:

  static constexpr bool exists = true;

  static constexpr MinMonoid<T> Zero() {
    return Bounded<MinMonoid<T>>::MaxValue();
  }

};

template <class T>
class Semigroup<MinMonoid<T>> {
public:

  static constexpr bool exists = true;

  static constexpr MinMonoid<T> Add(const MinMonoid<T>& lhs,
                                    const MinMonoid<T>& rhs) noexcept
  {
    switch (Ord<T>::Compare(lhs.Value(), rhs.Value)) {
      case Ordering::LESS:    return lhs;
      case Ordering::GREATER: return rhs;
      case Ordering::EQUAL:   return lhs;
    }
  }

};

template<class T>
class Monoid<MinMonoid<T>> {
public:

  static constexpr bool exists = true;

};

}
