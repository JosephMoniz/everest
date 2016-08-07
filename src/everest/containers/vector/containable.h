#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Containable<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& item, const Vector<T>& vector) noexcept {
    return vector.Contains(item);
  }

};

}