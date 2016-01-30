#ifndef TRAITOROUS_TRAITS_MONOID
#define TRAITOROUS_TRAITS_MONOID 1

#include "traits/lawful/semigroup.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template <class T>
class Monoid : public ZeroVal<T>, public Semigroup<T> {

  typedef Monoid<T> Base;

public:

  static constexpr bool exists = true;

};

template <class T>
class DefaultMonoid : public DefaultZeroVal<T>, public DefaultSemigroup<T> {
public:
  static constexpr bool exists = true;
};

}

#endif
