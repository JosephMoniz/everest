#pragma once

#include <utility>
#include <everest/memory/shared.h>
#include <everest/containers/option/option_type.h>

namespace everest {

template<class T>
class Option final {

  const OptionType _tag;

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
using SharedOption = Shared<Option<T>>;

template<class T>
const Option<T> Some(const T& option) {
  return Option<T>(option);
}

template<class T>
const Option<T> Some(T&& option) {
  return Option<T>(std::move(option));
}

template<class T>
const Option<T> None() {
  return Option<T>();
}

template<class T>
const SharedOption<T> SharedSome(const T &o) {
  return MakeShared<Option<T>>(o);
}

template<class T>
const SharedOption<T> SharedNone() {
  return MakeShared<Option<T>>();
}

template <class T, class N, class S, class R = typename std::result_of<N()>::type>
constexpr R Match(const Option<T>& o, N n, S s) noexcept {
  return (o.GetType() == OptionType::NONE)
    ? n()
    : s(o.Get());
}

template <class T, class N, class S, class R = typename std::result_of<N()>::type>
constexpr R Match(const SharedOption<T>& o, N n, S s) noexcept {
  return (o->GetType() == OptionType::NONE)
    ? n()
    : s(o->Get());
}

template <class T>
class Iteration<Option<T>> {
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

#include "everest/containers/option/traits/containable.h"
#include "everest/containers/option/traits/container.h"
#include "everest/containers/option/traits/alternative.h"
#include "everest/containers/option/traits/eq.h"
#include "everest/containers/option/traits/foldable.h"
#include "everest/containers/option/traits/functor.h"
#include "everest/containers/option/traits/hashable.h"
#include "everest/containers/option/traits/monad.h"
#include "everest/containers/option/traits/semigroup.h"
#include "everest/containers/option/traits/zero.h"
#include "everest/containers/option/traits/monoid.h"
#include "everest/containers/option/traits/filterable.h"
#include "everest/containers/option/traits/ord.h"
#include "everest/containers/option/traits/monad_plus.h"
#include "everest/containers/option/traits/unwrappable.h"
#include "everest/containers/option/traits/shows.h"

#include "everest/containers/option/traits/shared/containable.h"
#include "everest/containers/option/traits/shared/container.h"
#include "everest/containers/option/traits/shared/alternative.h"
#include "everest/containers/option/traits/shared/eq.h"
#include "everest/containers/option/traits/shared/foldable.h"
#include "everest/containers/option/traits/shared/functor.h"
#include "everest/containers/option/traits/shared/hashable.h"
#include "everest/containers/option/traits/shared/monad.h"
#include "everest/containers/option/traits/shared/semigroup.h"
#include "everest/containers/option/traits/shared/zero.h"
#include "everest/containers/option/traits/shared/monoid.h"
#include "everest/containers/option/traits/shared/filterable.h"
#include "everest/containers/option/traits/shared/ord.h"
#include "everest/containers/option/traits/shared/monad_plus.h"
#include "everest/containers/option/traits/shared/unwrappable.h"
#include "everest/containers/option/traits/shared/shows.h"
#include "everest/containers/option/traits/shared/enumerable.h"
