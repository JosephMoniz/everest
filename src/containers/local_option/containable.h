#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_CONTAINABLE_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_CONTAINABLE_H

#include "containers/option.h"
#include "traits/unlawful/containable.h"

namespace traitorous {

template <class T>
class LocalOption;

template <class T>
class Containable<LocalOption<T>, T> {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& n, const LocalOption<T>& f) noexcept {
    return Match(f,
      []()             { return false; },
      [&n](const T& m) { return n == m; }
    );
  }

};

}

#endif
