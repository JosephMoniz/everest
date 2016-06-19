#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class Containable<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& item, const MutableSet<T>& set) noexcept {
    return Containable<MutableVector<T>>::Contains(item, *set.GetConstBucket(item));
  }

};

}