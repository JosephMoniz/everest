#pragma once

#include <containers/option.h>
#include <traits/unlawful/container.h>

namespace traitorous {

template <class T>
class Option;

template <class T>
class Container<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const Option<T>& o) noexcept {
    return Match(o,
      []()           { return 0; },
      [](const T& n) { return 1; }
    );
  }

  static constexpr bool IsEmpty(const Option<T>& o) noexcept {
    return Match(o,
      []()           { return true; },
      [](const T& n) { return false; }
    );
  }

};

}
