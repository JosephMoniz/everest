#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template <class T>
class Takeable<Vector<T>> {
public:

  static constexpr bool exists = true;

  static Vector<T> Take(size_t length, const Vector<T>& vector) noexcept {
    return Vector<T>(Memory<T>(vector.Pointer(), Min(length, vector.Length())));
  }

  template<class Predicate>
  static Vector<T> TakeWhile(Predicate predicate, const Vector<T>& vector) noexcept {
    size_t offset = 0;
    size_t length = vector.Length();
    auto pointer  = vector.Pointer();
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    return Vector<T>(Memory<T>(pointer, offset));
  }

};

}