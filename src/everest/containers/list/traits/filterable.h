#pragma once

#include <utility>
#include <everest/containers/list.h>
#include <everest/traits/unlawful/filterable.h>

namespace everest {

template<class T>
using List = Shared<LocalList<T>>;

template <class T>
class Filterable<Vector<T>> {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static Vector<T> Filter(Predicate predicate, const List<T>& vector) noexcept {
    ListNode<T> head    = nullptr;
    ListNode<T> current = nullptr;

    /// end of the linex
    auto results = MutableVector<T>();
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (auto i = 0; i < length; i++) {
      if (predicate(pointer[i])) {
        results.Push(pointer[i]);
      }
    }
    return Vector<T>(std::move(results));
  }

};

}
