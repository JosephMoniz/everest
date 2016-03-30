#pragma once

#include "containers/array.h"
#include "traits/lawful/monoid.h"

namespace traitorous {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template<class T, size_t S>
class Monoid<SharedArray<T, S>> {
public:
  static constexpr bool exists = true;
};

}
