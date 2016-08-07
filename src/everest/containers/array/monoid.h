#pragma once

#include <everest/containers/array.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template <class T, size_t S>
class Array;

template<class T, size_t S>
class Monoid<Array<T, S>> final {
public:

  static constexpr bool exists = true;

};

}
