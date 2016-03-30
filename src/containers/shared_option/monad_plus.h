#pragma once

#include "containers/option.h"
#include "traits/lawful/monad_plus.h"

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class MonadPlus<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr SharedOption<T> MPlus(const SharedOption<T>& lhs, const SharedOption<T>& rhs) noexcept {
    return Match(lhs,
      [&rhs]()           { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }

};

}
