#pragma once

#include <everest/monoids/min_monoid.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template<class T>
class MinMonoid;

template<class T>
class Monoid<MinMonoid<T>> final {
public:

  static constexpr bool exists = true;

};

}