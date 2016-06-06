#pragma once

#include <everest/containers/array.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Semigroup<Array<T, S>> {
public:

  static constexpr bool exists = true;

  template <size_t Rs, size_t Ns = S + Rs>
  static constexpr SharedArray<T, S + Rs> Add(const Array<T, S>& lhs,
                                              const Array<T, Rs>& rhs) noexcept
  {
    auto newArray   = MakeSharedArray<T, Ns>();
    auto lhsPointer = Pointer(lhs);
    auto rhsPointer = Pointer(rhs);
    auto newPointer = newArray->MutablePointerAnnoyingHack();
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
