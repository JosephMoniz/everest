#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template <class T, size_t S>
class Array;

template<class T, size_t S>
class Ord<Array<T, S>> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const Array<T, S>& lhs, const Array<T, S>& rhs) noexcept {
    return lhs.Compare(rhs);
  }

  template<size_t Rs>
  static Ordering Compare(const Array<T, S>& lhs, const Array<T, Rs>& rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static const Array<T, S>& Min(const Array<T, S>& lhs, const Array<T, S>& rhs) noexcept {
    return lhs.Min(rhs);
  }

  static const Array<T, S>& Max(const Array<T, S>& lhs, const Array<T, S>& rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}
