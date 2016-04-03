#pragma once

#include <everest/containers/option.h>
#include <everest/containers/shared.h>
#include <everest/traits/lawful/monad_plus.h>

namespace everest {

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
