#pragma once

#include <everest/containers/shared.h>

namespace everest {

template<class T>
class LocalListNode;

template<class T>
using ListNode = Shared<LocalListNode<T>>;

template<class T>
class LocalList;

template<class T>
using List = Shared<LocalList<T>>;

template<class T>
class LocalListNode final {

  friend class Functor<List<T>>;

  friend class Semigroup<List<T>>;

  T _item;

  ListNode <T> _next;

  ListNode <T> setNext(const ListNode <T>& next) {
    _next = next;
    return next;
  }

public:

  LocalListNode(const T& item) noexcept : _item(item),
                                          _next(nullptr) { }

  LocalListNode(const T& item, const ListNode <T>& next) noexcept : _item(item),
                                                                    _next(next) { }

  LocalListNode(const LocalListNode<T>& other) : _item(other.Item()),
                                                 _next(other._next) { }

  const T& Item() const noexcept {
    return _item;
  }

  const ListNode<T> Next() const noexcept {
    return _next;
  }

};

}