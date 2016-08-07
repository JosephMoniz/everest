#pragma once

#include <everest/containers/set.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template <class T>
class Set;

template<class T>
class Monoid<Set<T>> final {
public:

  static constexpr bool exists = true;

};

}