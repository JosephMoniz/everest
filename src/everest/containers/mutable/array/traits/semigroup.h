#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template <class T, size_t S>
class Semigroup<MutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  template <size_t Rs, size_t Ns = S + Rs>
  static constexpr SharedMutableArray<T, S + Rs> Add(const MutableArray<T, S>& lhs,
                                                     const MutableArray<T, Rs>& rhs) noexcept
  {
    auto newArray   = MakeSharedMutableArray<T, Ns>();
    auto lhsPointer = lhs.Pointer();
    auto rhsPointer = rhs.Pointer();
    auto newPointer = newArray->MutablePointer();
    for (size_t i = 0; i < S; i++) {
      newPointer[i] = lhsPointer[i];
    }
    for (size_t i = 0; i < Rs; i++) {
      newPointer[i + S] = rhsPointer[i];
    }
    return newArray;
  }

};

}
