#ifndef TRAITOROUS_CONTAINERS_LIST_SHOWS_H
#define TRAITOROUS_CONTAINERS_LIST_SHOWS_H

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

  static const LocalString Show(const List<T>& list) noexcept {
    auto out = LocalString("List(");
    for (auto current = list->Head(); current.Pointer() != nullptr; current = current->Next()) {
      out = out + Shows<T>::Show(current->Item()) + LocalString(", ");
    }
    return Take(out, out.Length() - 2) + LocalString(")");
  }

};

}

#endif
