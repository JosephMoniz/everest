#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class Semigroup<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Add(const MutableVector<T>& lhs, const MutableVector<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}