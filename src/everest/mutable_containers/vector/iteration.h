#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Iteration<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableVector<T>& vector, F function) noexcept {
    vector.ForEach(function);
  }

};

}