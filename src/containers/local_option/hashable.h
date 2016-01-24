#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_HASHABLE_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_HASHABLE_H

#include "containers/local_option.h"
#include "traits/unlawful/hashable.h"

namespace traitorous {

template <class T>
class hashable<local_option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr int hash(const local_option<T>& o) noexcept {
    return match(o,
      []()           { return 0; },
      [](const T& n) { return hash(n); }
    );
  }

};

}

#endif

#pragma clang diagnostic pop