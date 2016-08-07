#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Eq<Option<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Option<T>& lhs, const Option<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}
