#ifndef TRAITOROUS_CONTAINERS_OPTION_HASHABLE_H
#define TRAITOROUS_CONTAINERS_OPTION_HASHABLE_H

#include "containers/option.h"
#include "traits/unlawful/hashable.h"

namespace traitorous {

template <class T>
class Hashable<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr int Hash(const Option<T>& o) noexcept {
    return Match(o,
      []()           { return 0; },
      [](const T& n) { return Hash(n); }
    );
  }

};

}

#endif
