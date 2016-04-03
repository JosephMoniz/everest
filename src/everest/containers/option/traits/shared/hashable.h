#pragma once

#include <everest/containers/option.h>
#include <everest/memory/shared.h>
#include <everest/containers/option/traits/hashable.h>

namespace everest {

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
