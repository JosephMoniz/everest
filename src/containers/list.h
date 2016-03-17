#ifndef TRAITOROUS_CONTAINERS_LIST_H
#define TRAITOROUS_CONTAINERS_LIST_H

#include <iostream>

#include "shared.h"

namespace traitorous {

template<class T>
class LocalListNode;

template<class T>
using ListNode = Shared<LocalListNode<T>>;

template<class T>
class LocalList;

template<class T>
using List = Shared<LocalList<T>>;

template<class T>
class LocalListNode {

  friend class Functor<List<T>>;
  friend class Semigroup<List<T>>;

  T _item;

  ListNode<T> _next;

  ListNode<T> setNext(const ListNode<T>& next) {
    _next = next;
    return next;
  }

public:

  LocalListNode(const T& item) noexcept : _item(item), _next(nullptr) {
    //
  }

  LocalListNode(const T& item, const ListNode<T>& next) noexcept : _item(item), _next(next) {
    //
  }

  LocalListNode(const LocalListNode<T>& other): _item(other.Item()), _next(other._next) {
    //
  }

  const T& Item() const noexcept {
    return _item;
  }

  const ListNode<T> Next() const noexcept {
    return _next;
  }

};

template<class T>
class LocalList {

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

#include "containers/list/containable.h"
#include "containers/list/container.h"
#include "containers/list/eq.h"
#include "containers/list/foldable.h"
#include "containers/list/functor.h"
#include "containers/list/monoid.h"
#include "containers/list/ord.h"
#include "containers/list/semigroup.h"
#include "containers/list/shows.h"
#include "containers/list/zero.h"

#endif
