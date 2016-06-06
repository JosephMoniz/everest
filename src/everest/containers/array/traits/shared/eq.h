#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/memory/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template<class T, size_t S>
class Eq<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const SharedArray<T, S>& lhs, const SharedArray<T, S>& rhs) noexcept {
    return Eq<Array<T, S>>::Equals(*lhs, *rhs);
  }

  template<size_t Rs>
  static bool Equals(const SharedArray<T, S>& lhs, const SharedArray<T, Rs>& rhs) noexcept {
    return false;
  }

};

}
