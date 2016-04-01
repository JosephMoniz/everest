#pragma once

#include <everest/containers/option.h>
#include <everest/traits/lawful/monoid.h>

namespace traitorous {

template <class T>
class Option;

template<class T>
class Monoid<Option<T>> {
public:

  static constexpr bool exists = true;

};

}
