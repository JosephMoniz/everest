#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/memory/shared.h>

namespace everest {

template<class T, size_t S>
using SharedMutableArray = Shared<MutableArray<T, S>>;

template<class T, size_t S>
class Eq<SharedMutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const SharedMutableArray<T, S>& lhs, const SharedMutableArray<T, S>& rhs) noexcept {
    return Eq<MutableArray<T, S>>::Equals(*lhs.Pointer(), *rhs.Pointer());
  }

  template<size_t Rs>
  static bool Equals(const SharedMutableArray<T, S>& lhs, const SharedMutableArray<T, Rs>& rhs) noexcept {
    return false;
  }

};

}
