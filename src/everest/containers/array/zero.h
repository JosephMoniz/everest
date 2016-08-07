#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template <class T, size_t S>
class Array;

template<class T, size_t S>
class ZeroVal<Array<T, S>> final {
public:

  static constexpr bool exists = true;

  static Array<T, S> Zero() noexcept {
    return Array<T, S>::Zero();
  }

};

}
