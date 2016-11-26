#pragma once

#include <everest/strings/string.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/unlawful/one.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/copyable.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template <class T>
class MutableGCounter final {

  using Self = MutableGCounter<T>;

  T _value;

public:

  MutableGCounter() noexcept : _value(ZeroVal<T>::Zero()) { }

  MutableGCounter(const T& number) noexcept : _value(number) { }

  MutableGCounter(const Self& other) = delete;

  MutableGCounter(Self&& other) noexcept : _value(std::move(other._value)) { }

  Self& operator=(const Self& other) = delete;

  Self& operator=(Self&& other) noexcept {
    _value = std::move(other._value);
    return *this;
  }

  Self& Increment() noexcept {
    _value += OneVal<T>::One();
    return *this;
  }

  Self& IncrementBy(const T& number) noexcept {
    _value += number;
    return *this;
  }

  T Value() const noexcept {
    return _value;
  }

  Self Copy() const noexcept {
    return Self(Copyable<T>::Copy(_value));
  }

  Self Add(const Self& other) const noexcept {
    return Self(Ord<T>::Max(_value, other.Value()));
  }

  Self& AddInPlace(const Self& other) noexcept {
    _value = Ord<T>::Max(_value, other.Value());
    return *this;
  }

  String Show() const noexcept {
    return String::Builder()
      .Add("MutableGCounter(")
      .Add(Shows<T>::Show(_value))
      .Add(")")
      .Build();
  }

  bool Equals(const Self& other) const noexcept {
    return _value == other.Value();
  }

  Ordering Compare(const Self& other) const noexcept {
    return Ord<T>::Compare(_value, other.Value());
  }

  Self Min(const Self& other) const noexcept {
    return Self(Ord<T>::Min(_value, other.Value()));
  }

  Self Max(const Self& other) const noexcept {
    return Self(Ord<T>::Max(_value, other.Value()));
  }

  static Self Zero() noexcept {
    return Self(ZeroVal<T>::Zero());
  }

};

template <class T>
class Copyable<MutableGCounter<T>> final {
public:

  static constexpr bool exists = true;

  static MutableGCounter<T> Copy(const MutableGCounter<T>& counter) noexcept {
    return counter.Copy();
  }

};

template <class T>
class Eq<MutableGCounter<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableGCounter<T>& lhs, const MutableGCounter<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

template <class T>
class Ord<MutableGCounter<T>> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const MutableGCounter<T>& lhs,
                          const MutableGCounter<T>& rhs) noexcept
  {
    return lhs.Compare(rhs);
  }

  static MutableGCounter<T> Min(const MutableGCounter<T>& lhs,
                                const MutableGCounter<T>& rhs) noexcept
  {
    return lhs.Min(rhs);
  }

  static MutableGCounter<T> Max(const MutableGCounter<T>& lhs,
                                const MutableGCounter<T>& rhs) noexcept
  {
    return lhs.Max(rhs);
  }

};

template <class T>
class Semigroup<MutableGCounter<T>> final {
public:

  static constexpr bool exists = true;

  static MutableGCounter<T> Add(const MutableGCounter<T>& lhs,
                                       const MutableGCounter<T>& rhs) noexcept
  {
    return lhs.Add(rhs);
  }

};


}
