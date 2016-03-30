#pragma once

#include "traits/unlawful/zero.h"
#include "containers/list.h"

namespace traitorous {

template<class T>
using List = Shared<LocalList<T>>;

template<class T>
class ZeroVal<List<T>> {
public:

  static constexpr bool exists = true;

  static constexpr List<T> Zero() noexcept {
    return Cons<T>();
  }

};

}
