#pragma once

#include <everest/traits/lawful/foldable.h>
#include <everest/containers/mutable/mutable_array.h>
#include <everest/memory/shared.h>

namespace everest {

template<class T, size_t S>
using SharedMutableArray = Shared<MutableArray<T, S>>;

template <class T, size_t S>
class Foldable<SharedMutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const SharedMutableArray<T, S>& array) noexcept {
    return Foldable<MutableArray<T, S>>::Fold(*array);
  }

  template <class Fn,
    class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const SharedMutableArray<T, S>& array) noexcept {
    return Foldable<MutableArray<T, S>>::FoldMap(f, *array);
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const SharedMutableArray<T, S>& array) noexcept
  {
    return Foldable<MutableArray<T, S>>::FoldR(f, init, *array);
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const SharedMutableArray<T, S>& array) noexcept
  {
    return Foldable<MutableArray<T, S>>::FoldL(f, init, *array);
  }

};

}
