#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Container<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const MutableVector<T>& vector) noexcept {
    return vector.Length();
  }

  static bool IsEmpty(const MutableVector<T>& vector) noexcept {
    return vector.IsEmpty();
  }

};

}