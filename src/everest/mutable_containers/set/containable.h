#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class Containable<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& item, const MutableSet<T>& set) noexcept {
    return set.Contains(item);
  }

};

}