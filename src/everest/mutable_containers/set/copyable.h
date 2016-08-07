#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

template<class T>
class MutableSet;

template<class T>
class Copyable<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static MutableSet<T> Copy(const MutableSet<T>& set) noexcept {
    return set.Copy();
  }

};

}