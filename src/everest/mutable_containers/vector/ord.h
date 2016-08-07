#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class Ord<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const MutableVector<T> &lhs, const MutableVector<T> &rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static const MutableVector<T>& Min(const MutableVector<T> &lhs, const MutableVector<T> &rhs) noexcept {
    return lhs.Min(rhs);
  }

  static const MutableVector<T>& Max(const MutableVector<T> &lhs, const MutableVector<T> &rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}