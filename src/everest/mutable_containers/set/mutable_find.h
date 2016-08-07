#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/unlawful/mutable/mutable_find.h>

namespace everest {

template <class T>
class MutableSet;

template <class T>
class MutableFind<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static T* FindInPlace(const T& item, MutableSet<T>& set) noexcept {
    return set.FindInPlace(item);
  }

};

}