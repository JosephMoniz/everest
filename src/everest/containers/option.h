#pragma once

#include <utility>
#include <everest/containers/option/option_type.h>
#include <everest/traits/unlawful/fundamental.h>
#include <everest/meta/nth_arg.h>

namespace everest {

template<class T>
class Option final {

  OptionType _tag;

  T _value;

public:

  Option() noexcept : _tag(OptionType::NONE) {}

  template<class U = T>
  Option(T value, typename std::enable_if<Fundamental<U>::exists>::type* = 0) noexcept : _tag(OptionType::SOME) {
    new (&_value) T(value);
  }

  Option(T&& value) noexcept : _tag(OptionType::SOME) {
    new (&_value) T(std::move(value));
  }

  ~Option() noexcept {
    if (_tag == OptionType::SOME) {
      reinterpret_cast<T*>(&_value)->~T();
    }
  }

  static Option<T> Some(const T& option) noexcept {
    return Option<T>(option);
  }

  static Option<T> Some(T&& option) noexcept {
    return Option<T>(std::forward<T>(option));
  }

  static Option<T> None() noexcept {
    return Option<T>();
  }

  OptionType GetType() const noexcept {
    return _tag;
  };

  const T& Get() const noexcept {
    return *reinterpret_cast<const T*>(&_value);
  }

  T&& GetMovable() const noexcept {
    return std::move(*reinterpret_cast<T*>((T*)&_value));
  }

  bool IsSome() const noexcept {
    return _tag == OptionType::SOME;
  }

  bool IsNone() const noexcept {
    return _tag == OptionType::NONE;
  }

  size_t Length() const noexcept {
    return IsSome()
      ? 1
      : 0;
  }

  bool IsEmpty() const noexcept {
    return IsNone();
  }

  bool Contains(const T& item) const noexcept {
    return IsSome() && Get() == item;
  }

  const Option<T>& Alt(const Option<T>& other) const noexcept {
    return IsSome()
      ? *this
      : other;
  }

  bool Equals(const Option<T>& other) const noexcept {
    if (IsSome()) {
      return other.IsSome() && Get() == other.Get();
    } else {
      return !other.IsSome();
    }
  }

  T Fold() const noexcept {
    return IsSome()
      ? Get()
      : ZeroVal<T>::Zero();
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  M FoldMap(Fn f) const noexcept {
    return IsSome()
      ? f(Get())
      : ZeroVal<M>::Zero();
  }

  template <class Fn, class B>
  B FoldR(const B& init, Fn f) const noexcept {
    return IsSome()
      ? f(init, Get())
      : init;
  }

  template <class Fn, class B>
  B FoldL(const B& init, Fn f) const noexcept {
    return IsSome()
      ? f(init, Get())
      : init;
  }

  template <class F, class B = typename std::result_of<F(T)>::type>
  Option<B> Map(F f) const noexcept {
    return IsSome()
      ? Option<B>::Some(f(Get()))
      : Option<B>::None();
  }

  HashValue Hash() const noexcept {
    return IsSome()
      ? Hashable<T>::Hash(Get())
      : HashValue(0u);
  }

  template <class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  Option<B> FlatMap(F f) const noexcept {
    return IsSome()
      ? f(Get())
      : Option<B>::None();
  }

  template <class B>
  Option<B> Then(const Option<B>& second) const noexcept {
    return IsSome()
      ? second
      : *this;
  }

  Option<T> Add(const Option<T>& other) const noexcept {
    if (IsSome()) {
      if (other.IsSome()) {
        return Option<T>::Some(Get() + other.Get());
      } else {
        return *this;
      }
    } else {
      return other;
    }
  }

  template <class P>
  Option<T> Filter(P predicate) const noexcept {
    if (IsSome()) {
      return predicate(Get())
        ? *this
        : Option<T>::None();
    } else {
      return Option<T>::None();
    }
  }

  Ordering Compare(const Option<T>& other) const noexcept {
    if (IsSome()) {
      if (other.IsSome()) {
        return Ord<T>::Compare(Get(), other.Get());
      } else {
        return Ordering::GREATER;
      }
    } else {
      if (other.IsSome()) {
        return Ordering::LESS;
      } else {
        return Ordering::EQUAL;
      }
    }
  }

  const Option<T>& Min(const Option<T>& other) const noexcept {
    return (Compare(other) == Ordering::GREATER)
      ? other
      : *this;
  }

  const Option<T>& Max(const Option<T>& other) const noexcept {
    return (Compare(other) == Ordering::LESS)
      ? other
      : *this;
  }

  const Option<T>& MPlus(const Option<T>& other) const noexcept {
    return IsSome()
      ? *this
      : other;
  }

  template <class F>
  T GetOrElse(F alternative) const noexcept {
    return IsSome()
      ? Get()
      : alternative();
  }

  T GetOrDefault(const T& alternative) const noexcept {
    return IsSome()
      ? Get()
      : alternative;
  }

  String Show() const noexcept {
    return IsSome()
      ? String("Some(") + Shows<T>::Show(Get()) + String(")")
      : String("None");
  }

  template <class N, class S>
  auto Match(N n, S s) noexcept -> decltype(n()) {
    return (GetType() == OptionType::NONE)
      ? n()
      : s(Get());
  }

  static Option<T> Zero() noexcept {
    return Option<T>::None();
  }

};

}
