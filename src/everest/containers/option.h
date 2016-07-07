#pragma once

#include <utility>
#include <everest/containers/option/option_type.h>
#include <everest/traits/unlawful/fundamental.h>

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

  OptionType GetType() const noexcept {
    return _tag;
  };

  const T& Get() const noexcept {
    return *reinterpret_cast<const T*>(&_value);
  }

  T&& GetMovable() const noexcept {
    return std::move(*reinterpret_cast<T*>((T*)&_value));
  }

};

template<class T>
Option<T> Some(const T& option) {
  return Option<T>(option);
}

template<class T>
Option<T> Some(T&& option) {
  return Option<T>(std::forward<T>(option));
}

template<class T>
Option<T> None() {
  return Option<T>();
}

template <class T, class N, class S>
auto Match(const Option<T>& o, N n, S s) noexcept -> decltype(n()) {
  return (o.GetType() == OptionType::NONE)
    ? n()
    : s(o.Get());
}

template <class T>
class Iteration<Option<T>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const Option<T>& container, const F& function) noexcept {
    if (container.GetType() == OptionType::SOME) {
      function(container.Get());
    }
  }

};

}

#include "everest/containers/option/containable.h"
#include "everest/containers/option/container.h"
#include "everest/containers/option/alternative.h"
#include "everest/containers/option/eq.h"
#include "everest/containers/option/foldable.h"
#include "everest/containers/option/functor.h"
#include "everest/containers/option/hashable.h"
#include "everest/containers/option/monad.h"
#include "everest/containers/option/semigroup.h"
#include "everest/containers/option/zero.h"
#include "everest/containers/option/monoid.h"
#include "everest/containers/option/filterable.h"
#include "everest/containers/option/ord.h"
#include "everest/containers/option/monad_plus.h"
#include "everest/containers/option/unwrappable.h"
#include "everest/containers/option/shows.h"
