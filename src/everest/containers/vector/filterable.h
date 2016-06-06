#pragma once

#include <utility>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/filterable.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Filterable<Vector<T>> {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static Vector<T> Filter(Predicate predicate, const Vector<T>& vector) noexcept {
    return Filterable<MutableVector<T>>::Filter(predicate, vector._wrapped);
  }

};

}
