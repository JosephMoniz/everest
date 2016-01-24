#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_CONTAINABLE_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_CONTAINABLE_H

#include "containers/local_option.h"
#include "traits/unlawful/containable.h"


namespace traitorous {

template <class T>
class containable<local_option, T> {
public:

  static constexpr bool exists = true;

  static constexpr bool contains(const T& n, const local_option<T>& f) noexcept {
    return match(f,
      []()             { return false; },
      [&n](const T& m) { return n == m; }
    );
  }

};

}

#endif
