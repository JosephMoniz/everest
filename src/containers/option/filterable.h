#ifndef TRAITOROUS_CONTAINERS_OPTION_FILTERABLE
#define TRAITOROUS_CONTAINERS_OPTION_FILTERABLE

#include "containers/option.h"
#include "traits/unlawful/filterable.h"

namespace traitorous {

template<class T>
using Option = Shared<LocalOption<T>>;

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

#endif