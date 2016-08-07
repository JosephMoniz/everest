#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class Copyable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Copy(const MutableVector<T>& vector) noexcept {
    return vector.Copy();
  }

};

}