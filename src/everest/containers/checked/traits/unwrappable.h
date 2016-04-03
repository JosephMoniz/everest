#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/unwrappable.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Unwrappable<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class D>
  static constexpr T GetOrElse(D d, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return d(); },
      [](const T& ok)     { return ok; }
    );
  }

  static constexpr T GetOrDefault(const T& d, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return d; },
      [](const T& ok)     { return ok; }
    );
  }

};

}