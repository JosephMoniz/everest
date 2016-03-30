#pragma once

#include "containers/option.h"
#include "traits/lawful/foldable.h"

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class Foldable<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const SharedOption<T>& n) noexcept {
    return Foldable<Option<T>>::Fold(*n);
  }

  template <class Fn,
            class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const SharedOption<T>& n) noexcept {
    return Foldable<Option<T>>::FoldMap(f, *n);
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const SharedOption<T>& n) noexcept
  {
    return Foldable<Option<T>>::FoldR(f, init, *n);
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const SharedOption<T>& n) noexcept
  {
    return Foldable<Option<T>>::FoldL(f, init, *n);
  }

};


}
