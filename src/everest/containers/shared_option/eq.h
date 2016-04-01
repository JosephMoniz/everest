#pragma once

#include <everest/containers/option.h>
#include <everest/containers/shared.h>
#include <everest/containers/option/eq.h>

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
