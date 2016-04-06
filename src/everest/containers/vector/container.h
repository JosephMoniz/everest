#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template <class T>
class Container<Vector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const Vector<T>& vector) noexcept {
    return vector.Length();
  }

  static constexpr bool IsEmpty(const Vector<T>& vector) noexcept {
    return vector.Length() == 0;
  }

};

}