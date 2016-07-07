#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Takeable<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static Vector<T> Take(size_t length, const Vector<T>& vector) noexcept {
    return Vector<T>(Takeable<MutableVector<T>>::Take(length, vector._wrapped));
  }

  template<class Predicate>
  static Vector<T> TakeWhile(Predicate predicate, const Vector<T>& vector) noexcept {
    return Vector<T>(Takeable<MutableVector<T>>::TakeWhile(predicate, vector._wrapped));
  }

};

}