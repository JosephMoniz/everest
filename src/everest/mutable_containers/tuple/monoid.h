#pragma once

#include <everest/mutable_containers/mutable_tuple.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template<class T, class U>
class MutableTuple;

template<class T, class U>
class Monoid<MutableTuple<T, U>> final {
public:

  static constexpr bool exists = true;

};

}