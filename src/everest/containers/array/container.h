#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Container<Array<T, S>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const Array<T, S>& array) noexcept {
    return array.Length();
  }

  static bool IsEmpty(const Array<T, S>& array) noexcept {
    return array.IsEmpty();
  }

};

}
