#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_CONTAINER_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_CONTAINER_H

#include "containers/local_option.h"
#include "traits/unlawful/container.h"

namespace traitorous {

template <class T>
class container<local_option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t length(const local_option<T>& o) noexcept {
    return match(o,
      []()           { return 0; },
      [](const T& n) { return 1; }
    );
  }

  static constexpr bool is_empty(const local_option<T>& o) noexcept {
    return match(o,
      []()           { return true; },
      [](const T& n) { return false; }
    );
  }

};

}

#endif
