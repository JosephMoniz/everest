#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class T, size_t S>
class Array;

template<class T, size_t S>
class Eq<Array<T, S>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Array<T, S>& lhs, const Array<T, S>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

  template<size_t Rs>
  static bool Equals(const Array<T, S>& lhs, const Array<T, Rs>& rhs) noexcept {
    return false;
  }

};

}
