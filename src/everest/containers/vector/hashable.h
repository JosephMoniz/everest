#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template <class T>
class Hashable<Vector<T>> {
public:

  static constexpr bool exists = true;

  static int Hash(const Vector<T>& vector) noexcept {
    int result   = 37;
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (size_t i = 0; i < length; i++) {
      result = 37 * result + Hash(pointer[i]);
    }
    return result;
  }

};

}