#pragma once

#include "containers/option.h"
#include "traits/lawful/monoid.h"

namespace traitorous {

template <class T>
class Option;

template<class T>
class Monoid<Option<T>> {
public:

  static constexpr bool exists = true;

};

}
