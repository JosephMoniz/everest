#pragma once

#include <everest/containers/set.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template<class T>
class Set;

template<class T>
class Semigroup<Set<T>> final {
public:

  static constexpr bool exists = true;

  static Set<T> Add(const Set<T>& lhs, const Set<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}