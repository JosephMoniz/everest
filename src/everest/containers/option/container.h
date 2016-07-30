#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Container<Option<T>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const Option<T>& o) noexcept {
    return Match(o,
      []()           { return 0u; },
      [](const T& n) { return 1u; }
    );
  }

  static bool IsEmpty(const Option<T>& o) noexcept {
    return Match(o,
      []()           { return true; },
      [](const T& n) { return false; }
    );
  }

};

}
