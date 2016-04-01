#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/container.h>

namespace traitorous {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Container<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const Array<T, S>& o) noexcept {
    return (size_t) S;
  }

  static constexpr bool IsEmpty(const Array<T, S>& o) noexcept {
    return S == 0;
  }

};

}
