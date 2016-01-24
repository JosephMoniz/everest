#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_UNWRAPPABLE_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_UNWRAPPABLE_H

#include "containers/local_option.h"
#include "traits/unlawful/unwrappable.h"

namespace traitorous {

template <class T>
class unwrappable<local_option<T>> {
public:

  static constexpr bool exists = true;

  template <class D>
  static constexpr T get_or_else(D d, const local_option<T>& f) noexcept {
    return match(f,
      [&d]()         { return d(); },
      [](const T& m) { return m; }
    );
  }

  static constexpr T get_or_default(const T& d, const local_option<T>& n) noexcept {
    return match(n,
      [&d]()         { return d; },
      [](const T& m) { return m; }
    );
  }

};

}

#endif
