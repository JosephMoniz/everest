#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Container<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const Vector<T>& vector) noexcept {
    return vector.Length();
  }

  static bool IsEmpty(const Vector<T>& vector) noexcept {
    return vector.IsEmpty();
  }

};

}