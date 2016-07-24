#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/filterable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Filterable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static MutableVector<T> Filter(Predicate predicate, const MutableVector<T>& vector) noexcept {
    return vector.Filter(predicate);
  }

};

}