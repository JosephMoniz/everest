#ifndef TRAITOROUS_CONTAINERS_LOCAL_ARRAY_FOLDABLE_H
#define TRAITOROUS_CONTAINERS_LOCAL_ARRAY_FOLDABLE_H

#include "traits/lawful/foldable.h"
#include "containers/array.h"

namespace traitorous {

template <class T, size_t S>
class Foldable<LocalArray<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const LocalArray<T, S>& array) noexcept {
    T memo = ZeroVal<T>::Zero();
    for (size_t i = 0; i < S; i++) {
      memo = Semigroup<T>::Add(memo, array.pointer()[i]);
    }
    return memo;
  }

  template <class Fn,
    class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const LocalArray<T, S>& array) noexcept {
    auto memo = ZeroVal<T>::Zero();
    for (size_t i = 0; i < S; i++) {
      memo = Semigroup<T>::Add(memo, f(array.pointer()[i]));
    }
    return memo;
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const LocalArray<T, S>& array) noexcept
  {
    auto memo = init;
    for (size_t i = S - 1; i != 0; i--) {
      memo = f(memo, array.pointer()[i]);
    }
    if (S > 0) {
      memo = f(memo, array.pointer()[0]);
    }
    return memo;
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const LocalArray<T, S>& array) noexcept
  {
    auto memo = init;
    for (size_t i = 0; i < S; i++) {
      memo = f(memo, array.pointer()[i]);
    }
    return memo;
  }

};

}

#endif
