#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class ZeroVal<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static Vector<T> Zero() noexcept {
    return Vector<T>::Zero();
  }

};

}