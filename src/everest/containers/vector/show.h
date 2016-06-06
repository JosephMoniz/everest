#pragma once

#include <everest/types/string.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Shows<Vector<T>> {
public:

  static constexpr bool exists = true;

  static const String Show(const Vector<T>& vector) noexcept {
    auto out     = String("Vector(");
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (size_t i = 0; i < length; i ++) {
      out = out + Shows<T>::Show(pointer[i]) + String(", ");
    }
    return Take(Length(out) - 2, out) + String(")");
  }

};

}