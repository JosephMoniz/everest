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
  static constexpr SharedArray<T, S + Rs> Add(const MutableArray<T, S>& lhs,
                                              const MutableArray<T, Rs>& rhs) noexcept
  {
    auto newArray = MakeSharedArray<T, Ns>();
    for (size_t i = 0; i < S; i++) {
      newArray->MutablePointer()[i] = lhs.Pointer()[i];
    }
    for (size_t i = 0; i < Rs; i++) {
      newArray->MutablePointer()[i + S] = rhs.Pointer()[i];
    }
    return newArray;
  }

};

}
