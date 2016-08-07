#pragma once

#include <everest/mutable_containers/mutable_array.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template<class T, size_t S>
class Ord<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const MutableArray<T, S> &lhs, const MutableArray<T, S> &rhs) noexcept {
    return lhs.Compare(rhs);
  }

  template<size_t Rs>
  static Ordering Compare(const MutableArray<T, S> &lhs, const MutableArray<T, Rs> &rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static const MutableArray<T, S>& Min(const MutableArray<T, S> &lhs, const MutableArray<T, S> &rhs) noexcept {
    return lhs.Min(rhs);
  }

  static const MutableArray<T, S>& Max(const MutableArray<T, S> &lhs, const MutableArray<T, S> &rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}
