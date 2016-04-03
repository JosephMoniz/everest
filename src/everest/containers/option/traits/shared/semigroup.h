#pragma once

#include <everest/containers/option.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class Semigroup<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr SharedOption<T> Add(const SharedOption<T>& lhs, const SharedOption<T>& rhs) noexcept {
    return Match(lhs,
      [&rhs]()        { return rhs; },
      [&](const T& x) {
        return Match(rhs,
          [&lhs]()        { return lhs; },
          [&](const T& y) { return SharedSome<T>(x + y); }
        );
      }
    );
  }

};

}
