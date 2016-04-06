#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template <class T>
class Containable<Vector<T>, T> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& n, const Vector<T>& vector) noexcept {
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (size_t i = 0; i < length; i++) {
      if (pointer[i] == n) {
        return true;
      }
    }
    return false;
  }

};

}