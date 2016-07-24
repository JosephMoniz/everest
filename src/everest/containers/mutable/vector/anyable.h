#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/anyable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Anyable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static bool Any(Predicate predicate, const MutableVector<T>& vector) noexcept {
    return vector.Any(predicate);
  }

};

}