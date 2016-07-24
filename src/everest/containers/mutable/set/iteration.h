#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class Iteration<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableSet<T>& container, F function) noexcept {
    container.ForEach(function);
  }

};

}