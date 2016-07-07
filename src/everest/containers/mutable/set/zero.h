#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template<class T>
class MutableSet;

template<class T>
class ZeroVal<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr MutableSet<T> Zero() noexcept {
    return MutableSet<T>();
  }

};

}