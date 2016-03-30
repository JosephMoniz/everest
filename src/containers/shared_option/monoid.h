#pragma once

#include "containers/option.h"
#include "traits/lawful/monoid.h"

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template<class T>
class Monoid<SharedOption<T>> {
public:

  static constexpr bool exists = true;

};

}
