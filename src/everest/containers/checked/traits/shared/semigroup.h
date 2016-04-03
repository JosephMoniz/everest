#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template <class E, class T>
class Semigroup<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr SharedChecked<E, T> Add(const SharedChecked<E, T>& lhs, const SharedChecked<E, T>& rhs) noexcept {
    return Match(lhs,
      [&](const E& errorLeft) { return lhs; },
      [&](const T& okLeft) {
        return Match(rhs,
          [&](const E& errorRight) { return rhs; },
          [&](const T& okRight)    { return MakeSharedOk<E, T>(okLeft + okRight); }
        );
      }
    );
  }

};

}