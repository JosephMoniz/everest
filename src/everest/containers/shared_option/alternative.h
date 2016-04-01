#pragma once

#include <everest/containers/option.h>
#include <everest/traits/lawful/alternative.h>
#include <everest/containers/shared.h>

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class Alternative<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr SharedOption<T> Alt(const SharedOption<T>& lhs, const SharedOption<T>& rhs) noexcept {
    return Match(lhs,
      [&rhs]()           { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }

};

}
