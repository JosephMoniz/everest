#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Pointable<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const MutableVector<T>& vector) noexcept {
    return (vector._memory != nullptr)
      ? Pointable<GrowableMemory<T>>::Pointer(vector._memory)
      : nullptr;
  }

};

}
