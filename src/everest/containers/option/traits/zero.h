#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

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

