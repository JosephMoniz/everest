#ifndef TRAITOROUS_CONTAINERS_ENUMERATORS_LIST_ENUMERATOR_H_H
#define TRAITOROUS_CONTAINERS_ENUMERATORS_LIST_ENUMERATOR_H_H

#include <containers/list.h>
#include <exceptions/no_such_element_exception.h>

namespace traitorous {

template<class T>
class ListEnumerator {

  ListNode<T> _next;

public:

  ListEnumerator(const List<T>& list) noexcept : _next(list->Head()) {
    //
  }

  ListEnumerator(const ListEnumerator<T>& enumerator) noexcept : _next(enumerator._next) {
    //
  }

  ListEnumerator(const ListEnumerator<T>&& enumerator) noexcept : _next(std::move(enumerator._next)) {
    //
  }

  ListEnumerator<T>& operator=(const ListEnumerator<T>& enumerator) noexcept {
    _next = enumerator._next;
    return *this;
  }

  bool HasNext() const noexcept {
    return _next != nullptr;
  }

  const T& Next() {
    if (HasNext()) {
      auto result = _next;
      _next       = _next->Next();
      return result;
    } else {
      throw NoSuchElementException();
    }
  }

};

}

#endif
