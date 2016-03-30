#pragma once

#include "containers/option.h"
#include "traits/unlawful/hashable.h"

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class Hashable<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr int Hash(const SharedOption<T>& o) noexcept {
    return Hashable<Option<T>>::Hash(*o);
  }

};

}
