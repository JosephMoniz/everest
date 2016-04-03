#pragma once

#include <everest/traits/lawful/functor.h>
#include <everest/containers/shared.h>
#include <everest/containers/list.h>

namespace everest {

template<class T>
using List = Shared<LocalList<T>>;

template<class T>
class Functor<List<T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr List<B> Map(F f, const List<T>& list) noexcept {
    ListNode<B> head    = nullptr;
    ListNode<B> current = nullptr;
    for (auto it = list->Head(); it.Pointer() != nullptr; it = it->Next()) {
      if (current.Pointer() == nullptr) {
        head    = MakeShared<LocalListNode<T>>(f(it->Item()));
        current = head;
      } else {
        current = current->setNext(MakeShared<LocalListNode<T>>(f(it->Item())));
      }
    }
    return MakeShared<LocalList<T>>(list->Length(), head);
  }

};

}
