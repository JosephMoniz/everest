#ifndef TRAITOROUS_OG_FOLDABLE_H
#define TRAITOROUS_OG_FOLDABLE_H

#include "traits/lawful/foldable.h"
#include "containers/array.h"

namespace traitorous {

template<class T, size_t S>
using Array = Shared<LocalArray<T, S>>;

template <class T, size_t S>
class Foldable<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const Array<T, S>& array) noexcept {
    return Foldable<LocalArray<T, S>>::Fold(*array.Pointer());
  }

  template <class Fn,
    class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const Array<T, S>& array) noexcept {
    return Foldable<LocalArray<T, S>>::FoldMap(f, *array.Pointer());
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const Array<T, S>& array) noexcept
  {
    return Foldable<LocalArray<T, S>>::FoldR(f, init, *array.Pointer());
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const Array<T, S>& array) noexcept
  {
    return Foldable<LocalArray<T, S>>::FoldL(f, init, *array.Pointer());
  }

};

}

#endif
