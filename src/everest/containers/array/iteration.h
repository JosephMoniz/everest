#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Iteration<Array<T, S>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const Array<T, S>& container, const F& function) noexcept {
    for (auto i = 0; i < S; i++) {
      function(container._array[i]);
    }
  }

};

}
