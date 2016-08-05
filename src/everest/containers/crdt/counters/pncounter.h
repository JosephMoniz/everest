#pragma once

#include <everest/containers/crdt/counters/gcounter.h>
#include <everest/types/string.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/negate.h>

namespace everest {

template<class T>
class PNCounter final {

  friend class Semigroup<PNCounter<T>>;

  GCounter<T> _positive;

  GCounter<T> _negative;

public:

  PNCounter() noexcept : _positive(), _negative() { }

  PNCounter(const T& number) noexcept {
    if (number >= 0) {
      _positive = GCounter<T>(number);
      _negative = GCounter<T>(ZeroVal<T>::Zero());
    } else {
      _positive = GCounter<T>(ZeroVal<T>::Zero());
      _negative = GCounter<T>(Negation<T>::Negate(number));
    }
  }

  PNCounter(const GCounter<T>& positive,
            const GCounter<T>& negative) noexcept : _positive(positive),
                                                    _negative(negative) { }

  PNCounter<T> Increment() const noexcept {
    return PNCounter(_positive + OneVal<T>::One(), _negative);
  }

  PNCounter<T> IncrementBy(const T& number) const noexcept {
    return PNCounter(_positive + number, _negative);
  }

  PNCounter<T> Decrement() const noexcept {
    return PNCounter(_positive, _negative + OneVal<T>::One());
  }

  PNCounter<T> DecrementBy(const T& number) const noexcept {
    return PNCounter(_positive, _negative + number);
  }

  T Value() const noexcept {
    return _positive.Value() - _negative.Value();
  }

};

template<class T>
class Shows<PNCounter<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const PNCounter<T>& counter) noexcept {
    return String("PNCounter(") + Shows<T>::Show(counter.Value()) + String(")");
  }

};

template<class T>
class Eq<PNCounter<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const PNCounter<T>& lhs, const PNCounter<T>& rhs) noexcept {
    return lhs.Value() == rhs.Value();
  }

};

template<class T>
class ZeroVal<PNCounter<T>> final {
public:

  static constexpr bool exists = true;

  static PNCounter<T> Zero() {
    return PNCounter(ZeroVal<GCounter<T>>::Zero(), ZeroVal<GCounter<T>>::Zero());
  }

};

template<class T>
class Semigroup<PNCounter<T>> final {
public:

  static constexpr bool exists = true;

  static PNCounter<T> Add(const PNCounter<T>& lhs, const PNCounter<T>& rhs) noexcept {
    return PNCounter(Max(lhs._positive, rhs._positive), Max(lhs._negative, rhs._negative));
  }

};

template<class T>
class Monoid<PNCounter<T>> final {
public:

  static constexpr bool exists = true;

};

}
