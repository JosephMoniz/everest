#pragma once

#include <utility>
#include <type_traits>
#include <everest/containers/option/option_type.h>
#include <everest/traits/unlawful/fundamental.h>
#include <everest/meta/nth_type_arg.h>

namespace everest {

template<class T>
class Option final {

  OptionType _tag;

  T _value;

public:

  Option() noexcept : _tag(OptionType::NONE), _value() { }

  template <class U = T>
  Option(T pointer, typename std::enable_if<std::is_pointer<U>::value>::type* = 0) noexcept {
    if (pointer != nullptr) {
      _tag   = OptionType::SOME;
      _value = pointer;
    } else {
      _tag   = OptionType::NONE;
      _value = nullptr;
    }
  }

  template <class U = T>
  Option(T&& value, typename std::enable_if<!std::is_pointer<U>::value>::type* = 0) noexcept : _tag(OptionType::SOME),
                                                                                               _value(std::move(value)) { }

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
    return _value;
  }

  T& GetMutable() noexcept {
    return _value;
  }

  T&& GetMovable() const noexcept {
    return std::move(_value);
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
  auto Map(F f) const noexcept -> decltype(Option<B>::Some(f(Get()))) {
    return IsSome()
      ? Option<B>::Some(f(Get()))
      : Option<B>::None();
  }

  HashValue Hash() const noexcept {
    return IsSome()
      ? Hashable<T>::Hash(Get())
      : HashValue(0u);
  }

  template <class F, class B = nth_type_arg<typename std::result_of<F(T)>::type, 0>>
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

  // TODO: Make trait
  // TODO: Make test
  template <class F>
  Option<T> OrElse(F alternative) const noexcept {
    return IsSome()
      ? *this
      : alternative();
  }

  String Show() const noexcept {
    if (IsSome()) {
      return String::Builder()
        . Add("Some(")
        . Add(Shows<T>::Show(Get()))
        . Add(")")
        . Build();
    } else {
      return String("None");
    }
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
