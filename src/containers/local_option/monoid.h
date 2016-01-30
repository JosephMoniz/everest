#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_MONOID_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_MONOID_H

#include "containers/local_option.h"
#include "traits/lawful/monoid.h"

namespace traitorous {

template<class T>
class Monoid<LocalOption<T>> {
public:

  static constexpr bool exists = true;

};

}

#endif
