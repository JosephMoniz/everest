#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Hashable<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static int Hash(const MutableVector<T>& vector) noexcept {
    int result = 37;
    ForEach(vector, [&](const T& item) {
      result = 37 * result + Hashable<T>::Hash(item);
    });
    return result;
  }

};

}