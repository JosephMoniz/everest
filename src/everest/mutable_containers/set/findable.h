#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/unlawful/findable.h>

namespace everest {

template <class T>
class MutableSet;

template <class T>
class Findable<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Find(const T& item, MutableSet<T>& set) noexcept {
    return set.Find(item);
  }

};

}