#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<MutableArray<T, S>>;

template<class T, size_t S>
class Eq<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const SharedArray<T, S>& lhs, const SharedArray<T, S>& rhs) noexcept {
    return Eq<MutableArray<T, S>>::Equals(*lhs.Pointer(), *rhs.Pointer());
  }

  template<size_t Rs>
  static bool Equals(const SharedArray<T, S>& lhs, const SharedArray<T, Rs>& rhs) noexcept {
    return false;
  }

};

}
