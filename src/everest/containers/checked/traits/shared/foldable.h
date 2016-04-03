#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/foldable.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template <class E, class T>
class Foldable<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const SharedChecked<E, T>& checked) noexcept {
    return Foldable<Checked<E, T>>::Fold(*checked);
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const SharedChecked<E, T>& checked) noexcept {
    return Foldable<Checked<E, T>>::FoldMap(f, *checked);
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f, const B& init, const SharedChecked<E, T>& checked) noexcept {
    return Foldable<Checked<E, T>>::FoldR(f, init, *checked);
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f, const B& init, const SharedChecked<E, T>& checked) noexcept {
    return Foldable<Checked<E, T>>::FoldL(f, init, *checked);
  }

};

}