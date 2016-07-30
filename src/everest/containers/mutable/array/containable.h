#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template <class T, size_t S>
class Containable<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& n, const MutableArray<T, S>& array) noexcept {
    return array.Contains(n);
  }

};

}
