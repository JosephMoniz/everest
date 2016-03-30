#pragma once

#include <type_traits>
#include <containers/shared.h>

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

  Option(const T& o) noexcept : _tag(OptionType::SOME) {
    new (&_value) T(o);
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

#include "containers/shared_option/containable.h"
#include "containers/shared_option/container.h"
#include "containers/shared_option/alternative.h"
#include "containers/shared_option/eq.h"
#include "containers/shared_option/foldable.h"
#include "containers/shared_option/functor.h"
#include "containers/shared_option/hashable.h"
#include "containers/shared_option/monad.h"
#include "containers/shared_option/semigroup.h"
#include "containers/shared_option/zero.h"
#include "containers/shared_option/monoid.h"
#include "containers/shared_option/filterable.h"
#include "containers/shared_option/ord.h"
#include "containers/shared_option/monad_plus.h"
#include "containers/shared_option/unwrappable.h"
#include "containers/shared_option/shows.h"
#include "containers/shared_option/enumerable.h"

#include "containers/option/containable.h"
#include "containers/option/container.h"
#include "containers/option/alternative.h"
#include "containers/option/eq.h"
#include "containers/option/foldable.h"
#include "containers/option/functor.h"
#include "containers/option/hashable.h"
#include "containers/option/monad.h"
#include "containers/option/semigroup.h"
#include "containers/option/zero.h"
#include "containers/option/monoid.h"
#include "containers/option/filterable.h"
#include "containers/option/ord.h"
#include "containers/option/monad_plus.h"
#include "containers/option/unwrappable.h"
#include "containers/option/shows.h"
