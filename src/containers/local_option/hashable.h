#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_HASHABLE_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_HASHABLE_H

#include "containers/local_option.h"
#include "traits/unlawful/hashable.h"

namespace traitorous {

template <class T>
class Hashable<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr int Hash(const LocalOption<T>& o) noexcept {
    return Match(o,
      []()           { return 0; },
      [](const T& n) { return Hash(n); }
    );
  }

};

}

#endif

#pragma clang diagnostic pop