#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/container.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template <class T, size_t S>
class Container<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const SharedArray<T, S>& o) noexcept {
    return Container<Array<T, S>>::Length(*o.Pointer());
  }

  static constexpr bool IsEmpty(const SharedArray<T, S>& o) noexcept {
    return Container<Array<T, S>>::IsEmpty(*o.Pointer());
  }

};

}
