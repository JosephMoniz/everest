#pragma once

#include <everest/containers/set.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template <class T>
class Set;

template <class T>
class Shows<Set<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const Set<T>& set) noexcept {
    return set.Show();
  }

};

}