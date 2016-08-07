#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_filter.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class MutableFilter<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static MutableSet<T>& FilterInPlace(Predicate predicate, MutableSet<T>& set) noexcept {
    return set.FilterInPlace(predicate);
  }

};

}