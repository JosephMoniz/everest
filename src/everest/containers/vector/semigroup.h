#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class Semigroup<Vector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Vector<T> Add(const Vector<T>& lhs, const Vector<T>& rhs) noexcept {
    return Vector<T>(Semigroup<MutableVector<T>>::Add(lhs._wrapped, rhs._wrapped));
  }

};

}