#pragma once

#include "containers/option.h"
#include "traits/unlawful/eq.h"

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class Eq<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr bool Equals(const SharedOption<T>& lhs, const SharedOption<T>& rhs) noexcept {
    return Eq<Option<T>>::Equals(*lhs, *rhs);
  }

};

}
