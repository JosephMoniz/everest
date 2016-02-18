#ifndef TRAITOROUS_CONTAINERS_LIST_H
#define TRAITOROUS_CONTAINERS_LIST_H

#include <string>
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

template <class T>
class Shows<List<T>> {
public:

  static constexpr bool exists = true;

  static const std::string Show(const List<T>& list) noexcept {
    std::string out = "List(";
    for (auto current = list->Head(); current.pointer() != nullptr; current = current->Next()) {
      out += Shows<T>::Show(current->Item()) + ", ";
    }
    out = out.substr(0, out.length() - 2);
    out += ")";
    return out;
  }

};

template<class T>
class Ord<List<T>> {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const List<T> &lhs, const List<T> &rhs) noexcept {
    if (lhs->Length() == rhs->Length()) {
      for (auto lCurrent = lhs->Head(), rCurrent = rhs->Head();
           lCurrent.pointer() != nullptr && rCurrent.pointer() != nullptr;
           lCurrent = lCurrent->Next(), rCurrent = rCurrent->Next())
      {
        auto result = Ord<T>::Compare(lCurrent->Item(), rCurrent->Item());
        if (result != EQUAL) {
          return result;
        }
      }
      return EQUAL;
    } else {
      return (lhs->Length() > rhs->Length())
        ? GREATER
        : LESS;
    }
  }

  static constexpr const List<T>& Min(const List<T> &lhs, const List<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == GREATER)
       ? rhs
       : lhs;
  }

  static constexpr const List<T>& Max(const List<T> &lhs, const List<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == LESS)
       ? rhs
       : lhs;
  }

};

template<class T>
class Eq<List<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const List<T>& lhs, const List<T>& rhs) noexcept {
    return Compare(lhs, rhs) == EQUAL;
  }

};

template<class T>
class Functor<List<T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr List<B> Map(F f, const List<T>& list) noexcept {
    ListNode<B> head    = nullptr;
    ListNode<B> current = nullptr;
    for (auto it = list->Head(); it.pointer() != nullptr; it = it->Next()) {
      if (current.pointer() == nullptr) {
        head    = MakeShared<LocalListNode<T>>(f(it->Item()));
        current = head;
      } else {
        current->setNext(MakeShared<LocalListNode<T>>(f(it->Item())));
        current = current->Next();
      }
    }
    return MakeShared<LocalList<T>>(list->Length(), head);
  }

};

template <class T>
class Containable<List<T>, T> {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& n, const List<T>& list) noexcept {
    for (auto it = list->Head(); it.pointer() != nullptr; it = it->Next()) {
      if (Eq<T>::Equals(it->Item(), n)) {
        return true;
      }
    }
    return false;
  }

};

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

template <class T>
class Semigroup<List<T>> {
public:

  static constexpr bool exists = true;

  static List<T> Add(const List<T>& lhs, const List<T>& rhs) noexcept {
    ListNode<T> head    = nullptr;
    ListNode<T> current = nullptr;
    for (auto it = lhs->Head(); it.pointer() != nullptr; it = it->Next()) {
      if (current.pointer() == nullptr) {
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

template<class T>
class ZeroVal<List<T>> {
public:

  static constexpr bool exists = true;

  static constexpr List<T> Zero() noexcept {
    return Cons<T>();
  }

};

template<class T>
class Monoid<List<T>> {
public:
  static constexpr bool exists = true;
};

}

#endif
