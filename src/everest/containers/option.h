#pragma once

#include <type_traits>
#include <everest/containers/shared.h>
#include <everest/types/string.h>

namespace traitorous {

enum class OptionType {
  SOME,
  NONE
};

template<>
class Shows<OptionType> {
public:

  static constexpr bool exists = true;

  static String Show(OptionType n) noexcept {
    switch(n) {
      case OptionType::SOME: return String("SOME");
      case OptionType::NONE: return String("NONE");
    }
  }

};

template<class T>
class Option final {

  using data_t = typename std::aligned_storage<sizeof(T), alignof(T)>::type;

  const OptionType _tag;

  data_t _value;

public:

  Option() noexcept : _tag(OptionType::NONE) {}

  Option(const T& value) noexcept : _tag(OptionType::SOME) {
    new (&_value) T(value);
  }

  Option(T&& value) noexcept : _tag(OptionType::SOME) {
    _value = std::move(value);
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

};

template<class T>
using SharedOption = Shared<Option<T>>;

template<class T>
const Option<T> Some(const T &o) {
  return Option<T>(o);
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

}

#include "everest/containers/shared_option/containable.h"
#include "everest/containers/shared_option/container.h"
#include "everest/containers/shared_option/alternative.h"
#include "everest/containers/shared_option/eq.h"
#include "everest/containers/shared_option/foldable.h"
#include "everest/containers/shared_option/functor.h"
#include "everest/containers/shared_option/hashable.h"
#include "everest/containers/shared_option/monad.h"
#include "everest/containers/shared_option/semigroup.h"
#include "everest/containers/shared_option/zero.h"
#include "everest/containers/shared_option/monoid.h"
#include "everest/containers/shared_option/filterable.h"
#include "everest/containers/shared_option/ord.h"
#include "everest/containers/shared_option/monad_plus.h"
#include "everest/containers/shared_option/unwrappable.h"
#include "everest/containers/shared_option/shows.h"
#include "everest/containers/shared_option/enumerable.h"

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
