#pragma once

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template <class T, size_t S>
class Array;

template<class T, size_t S>
class ZeroVal<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr Array<T, S> Zero() noexcept {
    return Array<T, S>({});
  }

};

}
