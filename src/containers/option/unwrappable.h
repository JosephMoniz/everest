#ifndef TRAITOROUS_CONTAINERS_OPTION_UNWRAPPABLE_H
#define TRAITOROUS_CONTAINERS_OPTION_UNWRAPPABLE_H

#include "containers/option.h"
#include "traits/unlawful/unwrappable.h"

namespace traitorous {

template <class T>
class Unwrappable<Option<T>> {
public:

  static constexpr bool exists = true;

  template <class D>
  static constexpr T GetOrElse(D d, const Option<T>& f) noexcept {
    return Match(f,
      [&d]()         { return d(); },
      [](const T& m) { return m; }
    );
  }

  static constexpr T GetOrDefault(const T& d, const Option<T>& n) noexcept {
    return Match(n,
      [&d]()         { return d; },
      [](const T& m) { return m; }
    );
  }

};

}

#endif
