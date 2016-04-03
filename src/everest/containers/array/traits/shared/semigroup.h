#pragma once

#include <everest/containers/array.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template <class T, size_t S>
class Semigroup<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  template <size_t Rs, size_t Ns = S + Rs>
  static constexpr SharedArray<T, S + Rs> Add(const SharedArray<T, S>& lhs, const SharedArray<T, Rs>& rhs) noexcept {
    return Semigroup<Array<T, S>>::Add(*lhs.Pointer(), *rhs.Pointer());
  }

};

}
