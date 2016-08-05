#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Hashable<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const Vector<T>& vector) noexcept {
    return vector._wrapped.Hash();
  }

};

}