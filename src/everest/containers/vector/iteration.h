#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template <class T>
class Vector;

template <class T>
class Iteration<Vector<T>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const Vector<T>& container, const F& function) noexcept {
    container.ForEach(function);
  }

};

}