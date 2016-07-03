#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class E, class T>
class Checked;

template<class E, class T>
class Eq<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr bool Equals(const Checked <E, T>& lhs, const Checked <E, T>& rhs) noexcept {
    return Match(lhs,
      [&](const E& errorLeft) {
        return Match(rhs,
          [&](const E& errorRight) { return errorLeft == errorRight; },
          [](const T& okRight)     { return false; }
        );
      },
      [&](const T& okLeft) {
        return Match(rhs,
          [](const E& errorLeft) { return false; },
          [&](const T& okRight)  { return okLeft == okRight; }
        );
      }
    );
  }

};

}