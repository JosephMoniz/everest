#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/unlawful/filterable.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class Filterable<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static MutableSet<T> Filter(Predicate predicate, const MutableSet<T>& set) noexcept {
    return set.Filter(predicate);
  }

};

}