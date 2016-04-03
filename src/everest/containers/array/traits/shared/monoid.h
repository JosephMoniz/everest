#pragma once

#include <everest/containers/array.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template<class T, size_t S>
class Monoid<SharedArray<T, S>> {
public:
  static constexpr bool exists = true;
};

}
