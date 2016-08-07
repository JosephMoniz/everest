#pragma once

#include <everest/containers/option.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Semigroup<Option<T>> final {
public:

  static constexpr bool exists = true;

  static Option<T> Add(const Option<T>& lhs, const Option<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}

