#pragma once

#include <everest/containers/list.h>
#include <everest/traits/unlawful/enumerator.h>
#include <everest/containers/option.h>

namespace everest {

template<class T>
class ListEnumerator {

  template<class T> 
  friend class Enumerator<ListEnumerator<T>>;

  ListNode<T> _next;

public:

  ListEnumerator(const List<T>& list) noexcept : _next(list->Head()) {
    //
  }

  ListEnumerator(const ListEnumerator<T>& other) noexcept : _next(other._next) {
    //
  }


  ListEnumerator<T>& operator=(const ListEnumerator<T>& enumerator) noexcept {
    _next = enumerator._next;
    return *this;
  }

};

template<class T>
class Enumerator<ListEnumerator<T>> {
public:

  static constexpr bool exists = true;

  static const Option<T> Next(const T& enumerator) noexcept {
    if (enumerator._next != nullptr) {
      auto result      = enumerator._next;
      enumerator._next = enumerator._next->Next();
      return Option<T>(result);
    } else {
      return Option<T>();
    }
  }

};

}
