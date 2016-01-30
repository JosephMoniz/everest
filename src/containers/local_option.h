#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_H

#include <type_traits>

namespace traitorous {

enum OptionType {
  OPTION_SOME,
  OPTION_NONE
};

template<class T>
class LocalOption {

  using data_t = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
  const OptionType _tag;
  data_t _value;

public:

  LocalOption() : _tag(OPTION_NONE) {}

  LocalOption(const T& o) : _tag(OPTION_SOME) {
    new (&_value) T(o);
  }

  ~LocalOption() noexcept {
    if (_tag == OPTION_SOME) {
      reinterpret_cast<T*>(&_value)->~T();
    }
  }

  OptionType get_type() const {
    return _tag;
  };

  const T& get() const {
    return *reinterpret_cast<const T*>(&_value);
  }

};

template<class T>
const LocalOption<T> LocalSome(const T &o) {
  return LocalOption<T>(o);
}

template<class T>
const LocalOption<T> LocalNone() {
  return LocalOption<T>();
}

template <class T,
          class N,
          class S,
          class R = typename std::result_of<N()>::type>
constexpr R Match(const LocalOption<T>& o, N n, S s) noexcept {
  return (o.get_type() == OPTION_NONE)
    ? n()
    : s(o.get());
}

}

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
