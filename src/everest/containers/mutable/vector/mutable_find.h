#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_find.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class MutableFind<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static T* FindInPlace(Predicate predicate, MutableVector<T>& vector) noexcept {
    auto pointer  = MutablePointer(vector._memory);
    auto length   = Length(vector);
    for (size_t i = 0; i < length; i++) {
      if (predicate(pointer[i])) {
        return &pointer[i];
      }
    }
    return nullptr;
  }

};

}