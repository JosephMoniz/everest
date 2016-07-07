#pragma once

#include <everest/containers/option.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template <class T>
class Option;

template<class T>
class Monoid<Option<T>> final {
public:

  static constexpr bool exists = true;

};

}
