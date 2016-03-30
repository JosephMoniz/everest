#pragma once

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/lawful/monoid.h"

namespace traitorous {

template <class T, size_t S>
class Array;

template<class T, size_t S>
class Monoid<Array<T, S>> {
public:
  static constexpr bool exists = true;
};

}
