#ifndef TRAITOROUS_CONTAINERS_ARRAY_SEMIGROUP_H
#define TRAITOROUS_CONTAINERS_ARRAY_SEMIGROUP_H

#include "containers/array.h"
#include "traits/lawful/semigroup.h"

namespace traitorous {

template <class T, size_t S>
class Semigroup<Array<T, S>> {
public:

  static constexpr bool exists = true;

  template <size_t Rs, size_t Ns = S + Rs>
  static constexpr Array<T, S + Rs> Add(const Array<T, S>& lhs, const Array<T, Rs>& rhs) noexcept {
    return Semigroup<LocalArray<T, S>>::Add(*lhs.pointer(), *rhs.pointer());
  }

};

}

#endif
