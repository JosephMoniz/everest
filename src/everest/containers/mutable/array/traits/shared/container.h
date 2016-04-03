#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/container.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<MutableArray<T, S>>;

template <class T, size_t S>
class Container<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const SharedArray<T, S>& o) noexcept {
    return Container<MutableArray<T, S>>::Length(*o.Pointer());
  }

  static constexpr bool IsEmpty(const SharedArray<T, S>& o) noexcept {
    return Container<MutableArray<T, S>>::IsEmpty(*o.Pointer());
  }

};

}
