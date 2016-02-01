#ifndef TRAITOROUS_CONTAINERS_OPTION_H
#define TRAITOROUS_CONTAINERS_OPTION_H

#include "containers/local_option.h"
#include "containers/shared.h"

namespace traitorous {

template<class T>
using Option = Shared<LocalOption<T>>;

template<class T>
const Option<T> Some(const T &o) {
  return MakeShared<LocalOption<T>>(o);
}

template<class T>
const Option<T> None() {
  return MakeShared<LocalOption<T>>();
}

template <class T,
          class N,
          class S,
          class R = typename std::result_of<N()>::type>
constexpr R Match(const Option<T>& o, N n, S s) noexcept {
  return (o->GetType() == OPTION_NONE)
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

#endif
