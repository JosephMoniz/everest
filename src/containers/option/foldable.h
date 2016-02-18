#ifndef TRAITOROUS_CONTAINERS_OPTION_FOLDABLE_H
#define TRAITOROUS_CONTAINERS_OPTION_FOLDABLE_H

#include "containers/option.h"
#include "traits/lawful/foldable.h"

namespace traitorous {

template <class T>
class Foldable<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const Option<T>& n) noexcept {
    return Foldable<LocalOption<T>>::Fold(*n.pointer());
  }

  template <class Fn,
            class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const Option<T>& n) noexcept {
    return Foldable<LocalOption<T>>::FoldMap(f, *n.pointer());
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const Option<T>& n) noexcept
  {
    return Foldable<LocalOption<T>>::FoldR(f, init, *n.pointer());
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const Option<T>& n) noexcept
  {
    return Foldable<LocalOption<T>>::FoldL(f, init, *n.pointer());
  }

};


}

#endif
