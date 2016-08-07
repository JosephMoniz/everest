#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/Pointable.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Containable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& n, const MutableVector<T>& vector) noexcept {
    return vector.Contains(n);
  }

};

}