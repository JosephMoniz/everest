#ifndef TRAITOROUS_TRAITS_MONOID
#define TRAITOROUS_TRAITS_MONOID 1

#include "traits/lawful/semigroup.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template <class T>
class monoid : public zero_val<T>, public semigroup<T> {

  typedef monoid<T> base;

public:

  static constexpr bool exists = true;

};

template <class T>
class default_monoid : public default_zero_val<T>, public default_semigroup<T> {
public:
  static constexpr bool exists = true;
};

}

#endif
