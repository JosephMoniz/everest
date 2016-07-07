#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Containable<Option<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& n, const Option<T>& f) noexcept {
    return Match(f,
      []()             { return false; },
      [&n](const T& m) { return n == m; }
    );
  }

};

}
