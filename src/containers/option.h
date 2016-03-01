#ifndef TRAITOROUS_CONTAINERS_OPTION_H
#define TRAITOROUS_CONTAINERS_OPTION_H

#include "containers/shared.h"
#include "containers/option.h"

namespace traitorous {

enum class OptionType {
  SOME,
  NONE
};

template<class T>
class LocalOption {

  using data_t = typename std::aligned_storage<sizeof(T), alignof(T)>::type;

  const OptionType _tag;

  data_t _value;

public:

  LocalOption() noexcept : _tag(OptionType::NONE) {}

  LocalOption(const T& o) noexcept : _tag(OptionType::SOME) {
    new (&_value) T(o);
  }

  ~LocalOption() noexcept {
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
using Option = Shared<LocalOption<T>>;

template<class T>
const LocalOption<T> LocalSome(const T &o) {
  return LocalOption<T>(o);
}

template<class T>
const LocalOption<T> LocalNone() {
  return LocalOption<T>();
}

template<class T>
const Option<T> Some(const T &o) {
  return MakeShared<LocalOption<T>>(o);
}

template<class T>
const Option<T> None() {
  return MakeShared<LocalOption<T>>();
}

template <class T, class N, class S, class R = typename std::result_of<N()>::type>
constexpr R Match(const LocalOption<T>& o, N n, S s) noexcept {
  return (o.GetType() == OptionType::NONE)
    ? n()
    : s(o.Get());
}

template <class T, class N, class S, class R = typename std::result_of<N()>::type>
constexpr R Match(const Option<T>& o, N n, S s) noexcept {
  return (o->GetType() == OptionType::NONE)
    ? n()
    : s(o->Get());
}

}

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
#include "containers/option/enumerable.h"

#include "containers/local_option/containable.h"
#include "containers/local_option/container.h"
#include "containers/local_option/alternative.h"
#include "containers/local_option/eq.h"
#include "containers/local_option/foldable.h"
#include "containers/local_option/functor.h"
#include "containers/local_option/hashable.h"
#include "containers/local_option/monad.h"
#include "containers/local_option/semigroup.h"
#include "containers/local_option/zero.h"
#include "containers/local_option/monoid.h"
#include "containers/local_option/filterable.h"
#include "containers/local_option/ord.h"
#include "containers/local_option/monad_plus.h"
#include "containers/local_option/unwrappable.h"
#include "containers/local_option/shows.h"

#endif
