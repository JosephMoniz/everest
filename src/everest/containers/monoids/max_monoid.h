#pragma once

#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/traits/lawful/semigroup.h>

namespace traitorous {

template<class T>
class MaxMonoid {

  friend class Eq<MaxMonoid<T>>;

  T _value;

public:

  MaxMonoid(const T& value) noexcept : _value(value) { }

  MaxMonoid(T&& value) noexcept : _value(std::move(value)) { }

  const T& Value() const noexcept {
    return _value;
  }

};

template<class T>
class Shows<MaxMonoid<T>> {
public:

  static constexpr bool exists = true;

  static String Show(const MaxMonoid<T>& monoid) noexcept {
    return String("MaxMonoid(") + Shows<T>::Show(monoid) + String(")");
  }

};

template<class T>
class Eq<MaxMonoid<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const MaxMonoid<T>& lhs, const MaxMonoid<T>& rhs) noexcept {
    return lhs.Value() == rhs.Value();
  }

};

template <class T>
class ZeroVal<MaxMonoid<T>> {
public:

  static constexpr bool exists = true;

  static constexpr MaxMonoid<T> Zero() {
    return Bounded<MaxMonoid<T>>::MinValue();
  }

};

template <class T>
class Semigroup<MaxMonoid<T>> {
public:

  static constexpr bool exists = true;

  static constexpr MaxMonoid<T> Add(const MaxMonoid<T>& lhs,
                                    const MaxMonoid<T>& rhs) noexcept
  {
    switch (Ord<T>::Compare(lhs.Value(), rhs.Value)) {
      case Ordering::LESS:    return rhs;
      case Ordering::GREATER: return lhs;
      case Ordering::EQUAL:   return lhs;
    }
  }

};

template<class T>
class Monoid<MaxMonoid<T>> {
public:

  static constexpr bool exists = true;

};

}
