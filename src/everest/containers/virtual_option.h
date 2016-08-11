#pragma once

#include <utility>
#include <everest/containers/option/option_type.h>
#include <everest/traits/unlawful/fundamental.h>
#include <everest/meta/nth_arg.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/unlawful/hashable.h>
#include <cassert>

namespace everest {

template<class T>
class VirtualOption {

  virtual OptionType GetType() const noexcept = 0;

  virtual const T& Get() const noexcept = 0;

  virtual T&& GetMovable() const noexcept = 0;

public:

  class Some final : public VirtualOption<T> {

    T _value;

  public:

    Some(const T& value) noexcept : _value(value) { }

    Some(T&& value) noexcept : _value(std::move(value)) { }

    OptionType GetType() const noexcept {
      return OptionType::SOME;
    }

    const T& Get() const noexcept {
      return _value;
    }

    T&& GetMovable() const noexcept {
      return std::move(_value);
    }

  };

  class None final : public VirtualOption<T> {
  public:

    None() noexcept { }

    OptionType GetType() const noexcept {
      return OptionType::NONE;
    }

    const T& Get() const noexcept {
      assert(false);
    }

    T&& GetMovable() const noexcept {
      assert(false);
    }

  };

  bool IsSome() const noexcept {
    return GetType() == OptionType::SOME;
  }

  bool IsNone() const noexcept {
    return GetType() == OptionType::NONE;
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

  const VirtualOption<T>& Alt(const VirtualOption<T>& other) const noexcept {
    return IsSome()
           ? *this
           : other;
  }

  bool Equals(const VirtualOption<T>& other) const noexcept {
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
  VirtualOption<B> Map(F f) const noexcept {
    return IsSome()
           ? VirtualOption<B>::Some(f(Get()))
           : VirtualOption<B>::None();
  }

  HashValue Hash() const noexcept {
    return IsSome()
           ? Hashable<T>::Hash(Get())
           : HashValue(0u);
  }

  template <class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  VirtualOption<B> FlatMap(F f) const noexcept {
    return IsSome()
           ? f(Get())
           : VirtualOption<B>::None();
  }

  template <class B>
  VirtualOption<B> Then(const VirtualOption<B>& second) const noexcept {
    return IsSome()
           ? second
           : *this;
  }

  VirtualOption<T> Add(const VirtualOption<T>& other) const noexcept {
    if (IsSome()) {
      if (other.IsSome()) {
        return VirtualOption<T>::Some(Get() + other.Get());
      } else {
        return *this;
      }
    } else {
      return other;
    }
  }

  template <class P>
  VirtualOption<T> Filter(P predicate) const noexcept {
    if (IsSome()) {
      return predicate(Get())
             ? *this
             : VirtualOption<T>::None();
    } else {
      return VirtualOption<T>::None();
    }
  }

  Ordering Compare(const VirtualOption<T>& other) const noexcept {
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

  const VirtualOption<T>& Min(const VirtualOption<T>& other) const noexcept {
    return (Compare(other) == Ordering::GREATER)
           ? other
           : *this;
  }

  const VirtualOption<T>& Max(const VirtualOption<T>& other) const noexcept {
    return (Compare(other) == Ordering::LESS)
           ? other
           : *this;
  }

  const VirtualOption<T>& MPlus(const VirtualOption<T>& other) const noexcept {
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

  static VirtualOption<T> Zero() noexcept {
    return VirtualOption<T>::None();
  }

};

}
