#pragma once

#include <everest/containers/set.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template <class T>
class Set;

template<class T>
class ZeroVal<Set<T>> final {
public:

  static constexpr bool exists = true;

  static Set<T> Zero() noexcept {
    return Set<T>::Zero();
  }

};

}