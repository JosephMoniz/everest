#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class Eq<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableVector<T>& lhs, const MutableVector<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}