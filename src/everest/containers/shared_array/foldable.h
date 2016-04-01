#pragma once

#include <everest/traits/lawful/foldable.h>
#include <everest/containers/array.h>
#include <everest/containers/shared.h>

namespace traitorous {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template <class T, size_t S>
class Foldable<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const SharedArray<T, S>& array) noexcept {
    return Foldable<Array<T, S>>::Fold(*array.Pointer());
  }

  template <class Fn,
    class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const SharedArray<T, S>& array) noexcept {
    return Foldable<Array<T, S>>::FoldMap(f, *array.Pointer());
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const SharedArray<T, S>& array) noexcept
  {
    return Foldable<Array<T, S>>::FoldR(f, init, *array.Pointer());
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const SharedArray<T, S>& array) noexcept
  {
    return Foldable<Array<T, S>>::FoldL(f, init, *array.Pointer());
  }

};

}
