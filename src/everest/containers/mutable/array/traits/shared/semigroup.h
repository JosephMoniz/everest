#pragma once

#include <everest/containers/array.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedMutableArray = Shared<MutableArray<T, S>>;

template <class T, size_t S>
class Semigroup<SharedMutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  template <size_t Rs, size_t Ns = S + Rs>
  static constexpr SharedMutableArray<T, S + Rs> Add(const SharedMutableArray<T, S>& lhs,
                                                     const SharedMutableArray<T, Rs>& rhs) noexcept
  {
    return Semigroup<MutableArray<T, S>>::Add(*lhs.Pointer(), *rhs.Pointer());
  }

};

}
