#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Hashable<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr int Hash(const Option<T>& o) noexcept {
    return Match(o,
      []()           { return 0; },
      [](const T& n) { return Hashable<T>::Hash(n); }
    );
  }

};

}

#pragma clang diagnostic pop
