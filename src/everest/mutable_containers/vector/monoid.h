#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class Monoid<MutableVector<T>> final {
public:
  static constexpr bool exists = true;
};

}