#pragma once

#include "containers/option.h"
#include "traits/unlawful/zero.h"

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template<class T>
class ZeroVal<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr SharedOption<T> Zero() {
    return SharedNone<T>();
  }

};

}
