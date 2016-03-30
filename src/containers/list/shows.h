#pragma once

#include <string>

#include "traits/unlawful/show.h"
#include "containers/list.h"

namespace traitorous {

template<class T>
using List = Shared<LocalList<T>>;

template <class T>
class Shows<List<T>> {
public:

  static constexpr bool exists = true;

  static const String Show(const List<T>& list) noexcept {
    auto out = String("List(");
    for (auto current = list->Head(); current.Pointer() != nullptr; current = current->Next()) {
      out = out + Shows<T>::Show(current->Item()) + String(", ");
    }
    return Take(out, out.Length() - 2) + String(")");
  }

};

}
