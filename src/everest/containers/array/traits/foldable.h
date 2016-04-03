#pragma once

#include <everest/traits/lawful/foldable.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/containers/array.h>

namespace everest {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Foldable<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const Array<T, S>& array) noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = array.Pointer();
    for (size_t i = 0; i < S; i++) {
      memo = Semigroup<T>::Add(memo, pointer[i]);
    }
    return memo;
  }

  template <class Fn,
    class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const Array<T, S>& array) noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = array.Pointer();
    for (size_t i = 0; i < S; i++) {
      memo = Semigroup<T>::Add(memo, f(pointer[i]));
    }
    return memo;
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const Array<T, S>& array) noexcept
  {
    auto memo    = init;
    auto pointer = array.Pointer();
    for (size_t i = S - 1; i; i--) {
      memo = f(memo, pointer[i]);
    }
    if (S > 0) {
      memo = f(memo, pointer[0]);
    }
    return memo;
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const Array<T, S>& array) noexcept
  {
    auto memo    = init;
    auto pointer = array.Pointer();
    for (size_t i = 0; i < S; i++) {
      memo = f(memo, pointer[i]);
    }
    return memo;
  }

};

}
