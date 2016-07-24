#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_remove_at.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class MutableRemoveAt<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T>& RemoveAtInPlace(size_t position, MutableVector<T>& vector) noexcept {
    return vector.RemoveAtInPlace(position);
  }

};

}