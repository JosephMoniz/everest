#pragma once

#include <everest/mutable_containers/mutable_array.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template <class T, size_t S>
class Hashable<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  HashValue Hash(const MutableArray<T, S>& array) noexcept {
    return array.Hash();
  }

};

}
