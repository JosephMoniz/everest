#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<MutableArray<T, S>>;

template <class T, size_t S>
class Semigroup<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  template <size_t Rs, size_t Ns = S + Rs>
  static constexpr SharedArray<T, S + Rs> Add(const SharedArray<T, S>& lhs, const SharedArray<T, Rs>& rhs) noexcept {
    return Semigroup<MutableArray<T, S>>::Add(*lhs.Pointer(), *rhs.Pointer());
  }

};

}
