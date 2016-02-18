#ifndef TRAITOROUS_CONTAINERS_LOCAL_ARRAY_SEMIGROUP_H
#define TRAITOROUS_CONTAINERS_LOCAL_ARRAY_SEMIGROUP_H

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/lawful/semigroup.h"

namespace traitorous {

template <class T, size_t S>
class Semigroup<LocalArray<T, S>> {
public:

  static constexpr bool exists = true;

  template <size_t Rs, size_t Ns = S + Rs>
  static constexpr Array<T, S + Rs> Add(const LocalArray<T, S>& lhs,
                                        const LocalArray<T, Rs>& rhs) noexcept
  {
    auto newArray = MakeArray<T, Ns>();
    for (size_t i = 0; i < S; i++) {
      newArray->mut_pointer()[i] = lhs.pointer()[i];
    }
    for (size_t i = 0; i < Rs; i++) {
      newArray->mut_pointer()[i + S] = rhs.pointer()[i];
    }
    return newArray;
  }

};

}

#endif
