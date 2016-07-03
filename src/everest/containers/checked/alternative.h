#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/alternative.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Alternative<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static Checked<E, T> Alt(const Checked<E, T>& lhs, const Checked<E, T>& rhs) noexcept {
    return Match(lhs,
      [&rhs](const E& error) { return rhs; },
      [&lhs](const T& ok)    { return lhs; }
    );
  }
};

}