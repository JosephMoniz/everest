#pragma once

#include <stddef.h>
#include <everest/containers/shared.h>
#include <everest/containers/list/list_node.h>

namespace everest {

template<class T>
class LocalList final {

  const size_t _length;

  const ListNode<T> _head;

public:

  LocalList(const size_t& length, const ListNode<T>& head) noexcept : _length(length), _head(head) {
    //
  }

  constexpr size_t Length() const noexcept {
    return _length;
  }

  constexpr ListNode<T> Head() const noexcept {
    return _head;
  }

};

template<class T>
List<T> Cons(const T& item, const List<T>& next) {
  return MakeShared<LocalList<T>>(
    next->Length() + 1,
    MakeShared<LocalListNode<T>>(item, next->Head())
  );
}

template<class T>
List<T> Cons(const T& item) {
  return MakeShared<LocalList<T>>(1, MakeShared<LocalListNode<T>>(item));
}

template<class T>
List<T> Cons() {
  return MakeShared<LocalList<T>>(0, nullptr);
}

template<class T>
ListNode<T> Cons(const T& item, const ListNode<T>& next) {
  return MakeShared<LocalListNode<T>>(item, next);
}

}

#include "everest/containers/list/traits/containable.h"
#include "everest/containers/list/traits/container.h"
#include "everest/containers/list/traits/eq.h"
#include "everest/containers/list/traits/foldable.h"
#include "everest/containers/list/traits/functor.h"
#include "everest/containers/list/traits/monoid.h"
#include "everest/containers/list/traits/ord.h"
#include "everest/containers/list/traits/semigroup.h"
#include "everest/containers/list/traits/shows.h"
#include "everest/containers/list/traits/zero.h"