#pragma once

#include <everest/containers/set.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template <class T>
class Set;

template <class T>
class Iteration<Set<T>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const Set<T>& container, const F& function) noexcept {
    return container.ForEach(function);
  }

};

}