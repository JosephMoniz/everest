#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Hashable<Option<T>> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const Option<T>& option) noexcept {
    return option.Hash();
  }

};

}

#pragma clang diagnostic pop
