#pragma once

#include <everest/containers/set.h>
#include <everest/traits/unlawful/filterable.h>

namespace everest {

template <class T>
class Set;

template <class T>
class Filterable<Set<T>> final {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static Set<T> Filter(Predicate predicate, const Set<T>& set) noexcept {
    return set.Filter(predicate);
  }

};

}