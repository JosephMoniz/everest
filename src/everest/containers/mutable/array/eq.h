#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template<class T, size_t S>
class Eq<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableArray<T, S>& lhs, const MutableArray<T, S>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

  template<size_t Rs>
  static bool Equals(const MutableArray<T, S>& lhs, const MutableArray<T, Rs>& rhs) noexcept {
    return false;
  }

};

}
