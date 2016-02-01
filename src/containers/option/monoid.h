#ifndef TRAITOROUS_CONTAINERS_OPTION_MONOID_H
#define TRAITOROUS_CONTAINERS_OPTION_MONOID_H

#include "containers/option.h"
#include "traits/lawful/monoid.h"

namespace traitorous {

template<class T>
class Monoid<Option<T>> {
public:

  static constexpr bool exists = true;

};

}

#endif
