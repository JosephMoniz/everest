#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Hashable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const MutableVector<T>& vector) noexcept {
    return vector.Hash();
  }

};

}