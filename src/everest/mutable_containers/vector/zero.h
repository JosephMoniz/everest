#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class ZeroVal<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr MutableVector<T> Zero() noexcept {
    return MutableVector<T>::Zero();
  }

};

}