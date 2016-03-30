#pragma once

#include "containers/option.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template <class T>
class Option;

template<class T>
class ZeroVal<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Option<T> Zero() {
    return None<T>();
  }

};

}

