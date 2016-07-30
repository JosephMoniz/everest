#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template <class T>
class Iteration;

template <class T, size_t S>
class Iteration<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableArray<T, S>& container, const F& function) noexcept {
    container.ForEach(function);
  }

};

}