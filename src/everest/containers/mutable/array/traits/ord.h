#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template<class T, size_t S>
class Ord<MutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const MutableArray<T, S> &lhs,
                          const MutableArray<T, S> &rhs) noexcept
  {
    for (size_t i = 0; i < S; i ++) {
      switch(Ord<T>::Compare(lhs.Pointer()[i], rhs.Pointer()[i])) {
        case Ordering::LESS:    return Ordering::LESS;
        case Ordering::GREATER: return Ordering::GREATER;
        case Ordering::EQUAL:   continue;
      }
    }
    return Ordering::EQUAL;
  }

  template<size_t Rs>
  static constexpr Ordering Compare(const MutableArray<T, S> &lhs,
                                    const MutableArray<T, Rs> &rhs) noexcept
  {
    return (S > Rs)
       ? Ordering::GREATER
       : Ordering::LESS;
  }

  static constexpr const MutableArray<T, S>& Min(const MutableArray<T, S> &lhs,
                                                 const MutableArray<T, S> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::GREATER)
       ? rhs
       : lhs;
  }

  static constexpr const MutableArray<T, S>& Max(const MutableArray<T, S> &lhs,
                                                 const MutableArray<T, S> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::LESS)
       ? rhs
       : lhs;
  }

};

}
