#pragma once

#include <everest/containers/monoids/min_monoid.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template<class T>
class Monoid<MinMonoid<T>> {
public:

static constexpr bool exists = true;

};

}