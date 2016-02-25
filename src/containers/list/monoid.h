#ifndef TRAITOROUS_CONTAINERS_LIST_MONOID_H
#define TRAITOROUS_CONTAINERS_LIST_MONOID_H

#include "traits/lawful/monoid.h"
#include "containers/list.h"

namespace traitorous {

template<class T>
using List = Shared<LocalList<T>>;

template<class T>
class Monoid<List<T>> {
public:
  static constexpr bool exists = true;
};

}

#endif
