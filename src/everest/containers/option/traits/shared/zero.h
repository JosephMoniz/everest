#pragma once

#include <everest/containers/option.h>
#include <everest/memory/shared.h>

namespace everest {

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
