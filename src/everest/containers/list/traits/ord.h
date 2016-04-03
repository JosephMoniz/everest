#pragma once

#include <everest/traits/unlawful/ord.h>
#include <everest/memory/shared.h>
#include <everest/containers/list.h>

namespace everest {

template<class T>
using List = Shared<LocalList<T>>;

template<class T>
class Ord<List<T>> {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const List<T> &lhs, const List<T> &rhs) noexcept {
    if (lhs->Length() == rhs->Length()) {
      for (auto lCurrent = lhs->Head(), rCurrent = rhs->Head();
           lCurrent.Pointer() != nullptr && rCurrent.Pointer() != nullptr;
           lCurrent = lCurrent->Next(), rCurrent = rCurrent->Next())
      {
        auto result = Ord<T>::Compare(lCurrent->Item(), rCurrent->Item());
        if (result != Ordering::EQUAL) {
          return result;
        }
      }
      return Ordering::EQUAL;
    } else {
      return (lhs->Length() > rhs->Length())
        ? Ordering::GREATER
        : Ordering::LESS;
  }
  }

  static constexpr const List<T>& Min(const List<T> &lhs, const List<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const List<T>& Max(const List<T> &lhs, const List<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
}

};

}
