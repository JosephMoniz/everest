#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class Semigroup<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static Vector<T> Add(const Vector<T>& lhs, const Vector<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}