#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_MONOID_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_MONOID_H

#include "containers/option.h"
#include "traits/lawful/monoid.h"

namespace traitorous {

template <class T>
class LocalOption;

template<class T>
class Monoid<LocalOption<T>> {
public:

  static constexpr bool exists = true;

};

}

#endif
