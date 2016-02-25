#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_CONTAINER_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_CONTAINER_H

#include "containers/option.h"
#include "traits/unlawful/container.h"

namespace traitorous {

template <class T>
class LocalOption;

template <class T>
class Container<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const LocalOption<T>& o) noexcept {
    return Match(o,
      []()           { return 0; },
      [](const T& n) { return 1; }
    );
  }

  static constexpr bool IsEmpty(const LocalOption<T>& o) noexcept {
    return Match(o,
      []()           { return true; },
      [](const T& n) { return false; }
    );
  }

};

}

#endif
