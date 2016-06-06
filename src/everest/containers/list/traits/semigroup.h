#pragma once

#include <everest/traits/lawful/semigroup.h>
#include <everest/memory/shared.h>
#include <everest/containers/list.h>

namespace everest {

template<class T>
using List = Shared<LocalList<T>>;

template <class T>
class Semigroup<List<T>> {
public:

  static constexpr bool exists = true;

  static List<T> Add(const List<T>& lhs, const List<T>& rhs) noexcept {
    ListNode<T> head    = nullptr;
    ListNode<T> current = nullptr;
    for (auto it = lhs->Head(); Pointer(it) != nullptr; it = it->Next()) {
      if (Pointer(current) == nullptr) {
        head    = MakeShared<LocalListNode<T>>(it->Item());
        current = head;
      } else {
        current->setNext(MakeShared<LocalListNode<T>>(it->Item()));
        current = current->Next();
      }
    }
    current->setNext(rhs->Head());
    return MakeShared<LocalList<T>>(rhs->Length() + rhs->Length(), head);
  }

};

}
