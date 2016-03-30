#pragma once

#include "traits/unlawful/containable.h"
#include "containers/list.h"

namespace traitorous {

template<class T>
using List = Shared<LocalList<T>>;

template <class T>
class Containable<List<T>, T> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& n, const List<T>& list) noexcept {
    for (auto it = list->Head(); it.Pointer() != nullptr; it = it->Next()) {
      if (Eq<T>::Equals(it->Item(), n)) {
        return true;
      }
    }
    return false;
  }

};

}
