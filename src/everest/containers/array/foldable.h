#pragma once

#include <everest/traits/lawful/foldable.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/containers/array.h>

namespace traitorous {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Foldable<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const Array<T, S>& array) noexcept {
    T memo = ZeroVal<T>::Zero();
    for (size_t i = 0; i < S; i++) {
      memo = Semigroup<T>::Add(memo, array.Pointer()[i]);
    }
    return memo;
  }

  template <class Fn,
    class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const Array<T, S>& array) noexcept {
    auto memo = ZeroVal<T>::Zero();
    for (size_t i = 0; i < S; i++) {
      memo = Semigroup<T>::Add(memo, f(array.Pointer()[i]));
    }
    return memo;
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const Array<T, S>& array) noexcept
  {
    auto memo = init;
    for (size_t i = S - 1; i != 0; i--) {
      memo = f(memo, array.Pointer()[i]);
    }
    if (S > 0) {
      memo = f(memo, array.Pointer()[0]);
    }
    return memo;
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const Array<T, S>& array) noexcept
  {
    auto memo = init;
    for (size_t i = 0; i < S; i++) {
      memo = f(memo, array.Pointer()[i]);
    }
    return memo;
  }

};

}