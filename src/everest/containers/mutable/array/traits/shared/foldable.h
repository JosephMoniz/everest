#pragma once

#include <everest/traits/lawful/foldable.h>
#include <everest/containers/mutable/mutable_array.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<MutableArray<T, S>>;

template <class T, size_t S>
class Foldable<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const SharedArray<T, S>& array) noexcept {
    return Foldable<MutableArray<T, S>>::Fold(*array.Pointer());
  }

  template <class Fn,
    class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const SharedArray<T, S>& array) noexcept {
    return Foldable<MutableArray<T, S>>::FoldMap(f, *array.Pointer());
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const SharedArray<T, S>& array) noexcept
  {
    return Foldable<MutableArray<T, S>>::FoldR(f, init, *array.Pointer());
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const SharedArray<T, S>& array) noexcept
  {
    return Foldable<MutableArray<T, S>>::FoldL(f, init, *array.Pointer());
  }

};

}
