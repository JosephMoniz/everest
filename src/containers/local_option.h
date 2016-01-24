#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_H

#include <type_traits>
#include <functional>
#include <string>
#include <memory>

#include "meta/nth_arg.h"

#include "traits/lawful/monoid.h"
#include "traits/unlawful/filterable.h"
#include "traits/unlawful/ord.h"
#include "traits/lawful/monad_plus.h"
#include "traits/unlawful/unwrappable.h"

namespace traitorous {

enum option_type {
  OPTION_SOME,
  OPTION_NONE
};

template<class T>
class local_option {

  using data_t = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
  const option_type _tag;
  data_t _value;

public:

  local_option() : _tag(OPTION_NONE) {}

  local_option(const T& o) : _tag(OPTION_SOME) {
    new (&_value) T(o);
  }

  ~local_option() noexcept {
    if (_tag == OPTION_SOME) {
      reinterpret_cast<T*>(&_value)->~T();
    }
  }

  option_type get_type() const {
    return _tag;
  };

  const T& get() const {
    return *reinterpret_cast<const T*>(&_value);
  }

};

template<class T>
const local_option<T> local_some(const T &o) {
  return local_option<T>(o);
}

template<class T>
const local_option<T> local_none() {
  return local_option<T>();
}

template <class T,
          class N,
          class S,
          class R = typename std::result_of<N()>::type>
static constexpr R match(const local_option<T>& o, N n, S s) noexcept {
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
