#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Iteration<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableVector<T>& vector, const F& function) noexcept {
    auto bucketSize    = Length(vector);
    auto bucketPointer = Pointer(vector);
    for (size_t i = 0; i < bucketSize; i++) {
      function(bucketPointer[i]);
    }
  }

};

}