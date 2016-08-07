#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class Ord<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const Vector<T>& lhs, const Vector<T>& rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static const Vector<T>& Min(const Vector<T>& lhs, const Vector<T>& rhs) noexcept {
    return lhs.Min(rhs);
  }

  static const Vector<T>& Max(const Vector<T>& lhs, const Vector<T>& rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}