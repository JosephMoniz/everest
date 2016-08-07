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

  static bool Contains(const T& item, const Option<T>& option) noexcept {
    return option.Contains(item);
  }

};

}
