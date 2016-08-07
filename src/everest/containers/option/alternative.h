#pragma once

#include <everest/containers/option.h>
#include <everest/traits/lawful/alternative.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Alternative<Option<T>> final {
public:

  static constexpr bool exists = true;

  static const Option<T>& Alt(const Option<T>& lhs, const Option<T>& rhs) noexcept {
    return lhs.Alt(rhs);
  }

};

}
