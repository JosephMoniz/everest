#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template<class T, size_t S>
class Monoid<MutableArray<T, S>> final {
public:
  static constexpr bool exists = true;
};

}
