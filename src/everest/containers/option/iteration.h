#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Iteration<Option<T>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const Option<T>& container, F function) noexcept {
    if (container.GetType() == OptionType::SOME) {
      function(container.Get());
    }
  }

};

}