#pragma once

#include <everest/types/string.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Shows<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const Vector<T>& vector) noexcept {
    auto out     = String("Vector(");
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (size_t i = 0; i < length; i++) {
      out = std::move(out) + Shows<T>::Show(pointer[i]) + String(", ");
    }
    return Take(out.Length() - 2, std::move(out)) + String(")");
  }

};

}