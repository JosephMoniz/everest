#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/foldable.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Foldable<Checked<E, T>> final {
public:

  static constexpr bool exists = true;

  static T Fold(const Checked<E, T>& checked) noexcept {
    return checked.Fold();
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  static M FoldMap(Fn f, const Checked<E, T>& checked) noexcept {
    return checked.FoldMap(f);
  }

  template <class Fn, class B>
  static B FoldR(Fn f, const B& init, const Checked<E, T>& checked) noexcept {
    return checked.FoldR(init, f);
  }

  template <class Fn, class B>
  static B FoldL(Fn f, const B& init, const Checked<E, T>& checked) noexcept {
    return checked.FoldL(init, f);
  }

};

}