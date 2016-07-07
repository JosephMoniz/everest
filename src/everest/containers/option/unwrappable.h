#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/unwrappable.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Unwrappable<Option<T>> final {
public:

  static constexpr bool exists = true;

  template <class D>
  static constexpr T GetOrElse(D d, const Option<T>& f) noexcept {
    return Match(f,
      [&d]()         { return d(); },
      [](const T& m) { return m; }
    );
  }

  static constexpr T GetOrDefault(const T& d, const Option<T>& n) noexcept {
    return Match(n,
      [&d]()         { return d; },
      [](const T& m) { return m; }
    );
  }

};

}

