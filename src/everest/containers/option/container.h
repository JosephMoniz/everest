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

  static size_t Length(const Option<T>& option) noexcept {
    return option.Length();
  }

  static bool IsEmpty(const Option<T>& option) noexcept {
    return option.IsEmpty();
  }

};

}
