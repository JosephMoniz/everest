#pragma once

#include <everest/strings/string.h>
#include <everest/traits/unlawful/negate.h>
#include <everest/traits/unlawful/copyable.h>
#include <everest/mutable_crdt/counters/mutable_gcounter.h>

namespace everest {

template<class T>
class MutablePNCounter final {

  using Self = MutablePNCounter<T>;

  using InnerCounter = MutableGCounter<T>;

  MutableGCounter<T> _positive;

  MutableGCounter<T> _negative;

public:

  MutablePNCounter() noexcept : _positive(), _negative() {}

  MutablePNCounter(const T& number) noexcept {
    if (number >= 0) {
      _positive = InnerCounter(number);
      _negative = InnerCounter(ZeroVal<T>::Zero());
    } else {
      _positive = InnerCounter(ZeroVal<T>::Zero());
      _negative = InnerCounter(Negation<T>::Negate(number));
    }
  }

  MutablePNCounter(InnerCounter&& positive,
                   InnerCounter&& negative) noexcept : _positive(std::move(positive)),
                                                       _negative(std::move(negative)) { }

  Self Copy() const noexcept {
    return Self(_positive.Copy(), _negative.Copy());
  }

  Self& Increment() noexcept {
    _positive.Increment();
    return *this;
  }

  Self& IncrementBy(const T& number) noexcept {
    _positive.IncrementBy(number);
    return *this;
  }

  Self& Decrement() noexcept {
    _negative.Increment();
    return *this;
  }

  Self& DecrementBy(const T& number) noexcept {
    _negative.IncrementBy(number);
    return *this;
  }

  T Value() const noexcept {
    return _positive.Value() - _negative.Value();
  }

  Self Add(const Self& other) const noexcept {
    return Self(_positive.Max(other._positive), _negative.Max(other._negative));
  }

  Self& AddInPlace(const Self& other) noexcept {
    _positive = _positive.Max(other._positive);
    _negative = _negative.Max(other._negative);
    return *this;
  }

  Ordering Compare(const Self& other) const noexcept {
    return Ord<T>::Compare(Value(), other.Value());
  }

  Self Min(const Self& other) const noexcept {
    return Self(Ord<T>::Min(Value(), other.Value()));
  }

  Self Max(const Self& other) const noexcept {
    return Self(Ord<T>::Max(Value(), other.Value()));
  }

  String Show() const noexcept {
    return String::Builder()
      .Add("MutablePNCounter(")
      .Add(Shows<T>::Show(Value()))
      .Add(")")
      .Build();
  }

  bool Equals(const Self& rhs) const noexcept {
    return Value() == rhs.Value();
  }

  static Self Zero() {
    return Self();
  }

};

template <class T>
class Copyable<MutablePNCounter<T>> final {
public:

  static constexpr bool exists = true;

  static MutablePNCounter<T> Copy(const MutablePNCounter<T>& counter) noexcept {
    return counter.Copy();
  }

};

template <class T>
class Eq<MutablePNCounter<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutablePNCounter<T>& lhs, const MutablePNCounter<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

template <class T>
class Ord<MutablePNCounter<T>> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const MutablePNCounter<T>& lhs,
                          const MutablePNCounter<T>& rhs) noexcept
  {
    return lhs.Compare(rhs);
  }

  static MutablePNCounter<T> Min(const MutablePNCounter<T>& lhs,
                                 const MutablePNCounter<T>& rhs) noexcept
  {
    return lhs.Min(rhs);
  }

  static MutablePNCounter<T> Max(const MutablePNCounter<T>& lhs,
                                 const MutablePNCounter<T>& rhs) noexcept
  {
    return lhs.Max(rhs);
  }

};

template <class T>
class Semigroup<MutablePNCounter<T>> final {
public:

  static constexpr bool exists = true;

  static MutablePNCounter<T> Add(const MutablePNCounter<T>& lhs,
                                 const MutablePNCounter<T>& rhs) noexcept
  {
    return lhs.Add(rhs);
  }

};

}