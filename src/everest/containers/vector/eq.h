#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class Eq<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Vector<T>& lhs, const Vector<T>& rhs) noexcept {
    return Eq<MutableVector<T>>::Equals(lhs._wrapped, rhs._wrapped);
  }

};

}