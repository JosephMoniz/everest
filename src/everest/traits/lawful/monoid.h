#pragma once


#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

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

