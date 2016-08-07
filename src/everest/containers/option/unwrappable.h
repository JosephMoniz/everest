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

  template <class F>
  static T GetOrElse(F alternative, const Option<T>& option) noexcept {
    return option.GetOrElse(alternative);
  }

  static T GetOrDefault(const T& alternative, const Option<T>& option) noexcept {
    return option.GetOrDefault(alternative);
  }

};

}

