#pragma once

#include <everest/containers/mutable/mutable_tuple.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template<class T, class U>
class MutableTuple;

template<class T, class U>
class Monoid<MutableTuple<T, U>> {
public:

  static constexpr bool exists = true;

};

}