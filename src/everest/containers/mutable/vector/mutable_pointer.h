#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

template <class T>
class MutableVector;

template<class T>
class MutablePointable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static T* Pointer(MutableVector<T>& vector) noexcept {
    return vector.MutablePointer();
  }

};

}