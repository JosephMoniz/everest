#ifndef TRAITOROUS_OG_ORD_H
#define TRAITOROUS_OG_ORD_H

#include "traits/unlawful/ord.h"
#include "containers/list.h"

namespace traitorous {

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

}

#endif
