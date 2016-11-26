#pragma once

#include <everest/crdt/counters/grow_only_counter.h>
#include <everest/strings/string.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/negate.h>

namespace everest {

template<class T>
class PositiveNegativeCounter final {

  friend class Semigroup<PositiveNegativeCounter<T>>;

  GrowOnlyCounter<T> _positive;

  GrowOnlyCounter<T> _negative;

public:

  PositiveNegativeCounter() noexcept : _positive(), _negative() { }

  PositiveNegativeCounter(const T& number) noexcept {
    if (number >= 0) {
      _positive = GrowOnlyCounter<T>(number);
      _negative = GrowOnlyCounter<T>(ZeroVal<T>::Zero());
    } else {
      _positive = GrowOnlyCounter<T>(ZeroVal<T>::Zero());
      _negative = GrowOnlyCounter<T>(Negation<T>::Negate(number));
    }
  }

  PositiveNegativeCounter(const GrowOnlyCounter<T>& positive,
            const GrowOnlyCounter<T>& negative) noexcept : _positive(positive),
                                                    _negative(negative) { }

  PositiveNegativeCounter<T> Increment() const noexcept {
    return PositiveNegativeCounter(_positive + OneVal<T>::One(), _negative);
  }

  PositiveNegativeCounter<T> IncrementBy(const T& number) const noexcept {
    return PositiveNegativeCounter(_positive + number, _negative);
  }

  PositiveNegativeCounter<T> Decrement() const noexcept {
    return PositiveNegativeCounter(_positive, _negative + OneVal<T>::One());
  }

  PositiveNegativeCounter<T> DecrementBy(const T& number) const noexcept {
    return PositiveNegativeCounter(_positive, _negative + number);
  }

  T Value() const noexcept {
    return _positive.Value() - _negative.Value();
  }

  PositiveNegativeCounter<T> Add(const PositiveNegativeCounter<T>& rhs) const noexcept {
    return PositiveNegativeCounter<T>(Max(_positive, rhs._positive), Max(_negative, rhs._negative));
  }

  String Show() const noexcept {
    return String("PNCounter(") + Shows<T>::Show(Value()) + String(")");
  }

  bool Equals(const PositiveNegativeCounter<T>& rhs) const noexcept {
    return Value() == rhs.Value();
  }

  static PositiveNegativeCounter<T> Zero() {
    return PositiveNegativeCounter<T>(ZeroVal<GrowOnlyCounter<T>>::Zero(), ZeroVal<GrowOnlyCounter<T>>::Zero());
  }

};

template<class T>
class Shows<PositiveNegativeCounter<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const PositiveNegativeCounter<T>& counter) noexcept {
    return counter.Show();
  }

};

template<class T>
class Eq<PositiveNegativeCounter<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const PositiveNegativeCounter<T>& lhs, const PositiveNegativeCounter<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

template<class T>
class ZeroVal<PositiveNegativeCounter<T>> final {
public:

  static constexpr bool exists = true;

  static PositiveNegativeCounter<T> Zero() {
    return PositiveNegativeCounter<T>::Zero();
  }

};

template<class T>
class Semigroup<PositiveNegativeCounter<T>> final {
public:

  static constexpr bool exists = true;

  static PositiveNegativeCounter<T> Add(const PositiveNegativeCounter<T>& lhs, const PositiveNegativeCounter<T>& rhs) noexcept {
    return PositiveNegativeCounter(Max(lhs._positive, rhs._positive), Max(lhs._negative, rhs._negative));
  }

};

template<class T>
class Monoid<PositiveNegativeCounter<T>> final {
public:

  static constexpr bool exists = true;

};

}
