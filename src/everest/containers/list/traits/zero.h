#pragma once

#include <everest/containers/shared.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/containers/list.h>

namespace everest {

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
