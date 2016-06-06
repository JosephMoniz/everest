#pragma once

#include <everest/containers/monoids/max_monoid.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template<class T>
class MaxMonoid;

template<class T>
class Monoid<MaxMonoid<T>> {
public:

  static constexpr bool exists = true;

};


}