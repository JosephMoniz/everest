#ifndef TRAITOROUS_CONTAINERS_LIST_EQ_H
#define TRAITOROUS_CONTAINERS_LIST_EQ_H

#include "traits/unlawful/eq.h"
#include "containers/list.h"

namespace traitorous {

template<class T>
using List = Shared<LocalList<T>>;

template<class T>
class Eq<List<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const List<T>& lhs, const List<T>& rhs) noexcept {
    return Compare(lhs, rhs) == EQUAL;
  }

};

}

#endif
