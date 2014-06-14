#ifndef TRAITOROUS_TRAITS_MONOID
#define TRAITOROUS_TRAITS_MONOID 1

#include "semigroup.h"
#include "zero.h"

namespace traitorous {

template <class T>
struct monoid : public zero_val<T>, public semigroup<T> {
  static constexpr bool exists = false;
};

template <class T>
struct default_monoid : public default_zero_val<T>, public default_semigroup<T> {
  static constexpr bool exists = true;
};

}

#endif
