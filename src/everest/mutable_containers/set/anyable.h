#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/unlawful/anyable.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class Anyable<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static bool Any(Predicate predicate, const MutableSet<T>& set) noexcept {
    return set.Any(predicate);
  }

};

}