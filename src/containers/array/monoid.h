#ifndef TRAITOROUS_CONTAINERS_ARRAY_MONOID_H
#define TRAITOROUS_CONTAINERS_ARRAY_MONOID_H

#include "containers/array.h"
#include "traits/lawful/monoid.h"

namespace traitorous {

template<class T, size_t S>
using Array = Shared<LocalArray<T, S>>;

template<class T, size_t S>
class Monoid<Array<T, S>> {
public:
  static constexpr bool exists = true;
};

}

#endif
