#pragma once

#include <everest/containers/option.h>
#include <everest/containers/shared.h>
#include <everest/traits/unlawful/filterable.h>

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class Filterable<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  template <class P>
  static constexpr SharedOption<T> Filter(P p, const SharedOption<T>& n) noexcept {
    return Match(n,
      []()            { return SharedNone<T>(); },
      [&](const T& m) { return p(m) ? n : SharedNone<T>(); }
    );
  }

};

}
