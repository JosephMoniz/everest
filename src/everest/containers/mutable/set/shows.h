#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class Shows<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const MutableSet<T>& set) noexcept {
    return set.Show();
  }

};

}