#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template<class T>
class ZeroVal<Vector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Vector<T> Zero() noexcept {
    return Vector<T>(Memory<T>());
  }

};

}