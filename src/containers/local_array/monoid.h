#ifndef TRAITOROUS_CONTAINERS_LOCAL_ARRAY_MONOID_H
#define TRAITOROUS_CONTAINERS_LOCAL_ARRAY_MONOID_H

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/lawful/monoid.h"

namespace traitorous {

template<class T, size_t S>
class Monoid<LocalArray<T, S>> {
public:
  static constexpr bool exists = true;
};

}

#endif
