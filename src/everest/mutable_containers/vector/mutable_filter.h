#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_filter.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class MutableFilter<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static MutableVector<T>& FilterInPlace(Predicate predicate, MutableVector<T>& vector) noexcept {
    return vector.FilterInPlace(predicate);
  }

};

}