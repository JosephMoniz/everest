#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/container.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedMutableArray = Shared<MutableArray<T, S>>;

template <class T, size_t S>
class Container<SharedMutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const SharedMutableArray<T, S>& o) noexcept {
    return Container<MutableArray<T, S>>::Length(*o.Pointer());
  }

  static constexpr bool IsEmpty(const SharedMutableArray<T, S>& o) noexcept {
    return Container<MutableArray<T, S>>::IsEmpty(*o.Pointer());
  }

};

}
