#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Pointable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const MutableVector<T>& vector) noexcept {
    return vector.Pointer();
  }

};

}
