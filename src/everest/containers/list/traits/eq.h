#pragma once

#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/containers/list.h>
#include <everest/memory/shared.h>

namespace everest {

template<class T>
using List = Shared<LocalList<T>>;

template<class T>
class Eq<List<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const List<T>& lhs, const List<T>& rhs) noexcept {
    return Compare(lhs, rhs) == Ordering::EQUAL;
  }

};

}
