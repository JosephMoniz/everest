#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/filterable.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Filterable<Option<T>> {
public:

  static constexpr bool exists = true;

  template <class P>
  static constexpr Option<T> Filter(P p, const Option<T>& n) noexcept {
    return Match(n,
      []()            { return None<T>(); },
      [&](const T& m) { return p(m) ? n : None<T>(); }
    );
  }

};

}
