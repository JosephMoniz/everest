#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Hashable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static int Hash(const MutableVector<T>& vector) noexcept {
    return vector.Hash();
  }

};

}