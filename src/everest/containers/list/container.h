#pragma once

#include <everest/traits/unlawful/container.h>
#include <everest/containers/list.h>
#include <everest/containers/shared.h>

namespace traitorous {

template<class T>
using List = Shared<LocalList<T>>;

template <class T>
class Container<List<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const List<T>& list) noexcept {
    return list->Length();
  }

  static constexpr bool IsEmpty(const List<T>& list) noexcept {
    return list->Length() == 0;
  }

};

}
