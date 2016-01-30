#ifndef TRAITOROUS_CONTAINERS_OPTION_CONTAINABLE_H
#define TRAITOROUS_CONTAINERS_OPTION_CONTAINABLE_H

#include "containers/option.h"
#include "traits/unlawful/containable.h"

namespace traitorous {

template <class T>
class Containable<Option<T>, T> {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& n, const Option <T>& f) noexcept {
    return Match(f,
      []()             { return false; },
      [&n](const T& m) { return n == m; }
    );
  }

};

}

#endif
