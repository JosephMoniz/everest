#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/pointable.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Anyable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static constexpr bool Any(Predicate predicate, const MutableVector<T>& vector) noexcept {
    auto pointer  = Pointer(vector);
    auto length   = Length(vector);
    for (size_t i = 0; i < length; i++) {
      if (predicate(pointer[i])) {
        return true;
      }
    }
    return false;
  }

};

}