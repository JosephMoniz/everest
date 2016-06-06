#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/memory/shared.h>

namespace everest {

template<class T, size_t S>
using SharedMutableArray = Shared<MutableArray<T, S>>;

template <class T, size_t S>
class Hashable<SharedMutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  static int Hash(const SharedMutableArray<T, S>& array) noexcept {
    Hashable<MutableArray<T, S>>::Hash(*array);
  }

};

}
