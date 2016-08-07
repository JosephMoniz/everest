#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/takeable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Takeable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Take(size_t length, const MutableVector<T>& vector) noexcept {
    return vector.Take(length);
  }

  template<class Predicate>
  static MutableVector<T> TakeWhile(Predicate predicate, const MutableVector<T>& vector) noexcept {
    return vector.TakeWhile(predicate);
  }

};

}