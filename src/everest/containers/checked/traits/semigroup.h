#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Semigroup<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr Checked<E, T> Add(const Checked<E, T>& lhs, const Checked<E, T>& rhs) noexcept {
    return Match(lhs,
      [&](const E& errorLeft) { return lhs; },
      [&](const T& okLeft) {
        return Match(rhs,
          [&](const E& errorRight) { return rhs; },
          [&](const T& okRight)    { return Ok<E, T>(okLeft + okRight); }
        );
      }
    );
  }

};

}