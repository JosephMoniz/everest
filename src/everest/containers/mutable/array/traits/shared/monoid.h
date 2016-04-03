#pragma once

#include <everest/containers/array.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/memory/shared.h>

namespace everest {

template<class T, size_t S>
using SharedMutableArray = Shared<MutableArray<T, S>>;

template<class T, size_t S>
class Monoid<SharedMutableArray<T, S>> {
public:
  static constexpr bool exists = true;
};

}
