#pragma once

#include <everest/traits/lawful/foldable.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/containers/array.h>

namespace everest {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Foldable<Array<T, S>> final {
public:

  static constexpr bool exists = true;

  static T Fold(const Array<T, S>& array) noexcept {
    return array.Fold();
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  static M FoldMap(Fn f, const Array<T, S>& array) noexcept {
    return array.FoldMap(f);
  }

  template <class Fn, class B>
  static B FoldR(Fn f, const B& init, const Array<T, S>& array) noexcept {
    return array.FoldR(init, f);
  }

  template <class Fn, class B>
  static B FoldL(Fn f, const B& init, const Array<T, S>& array) noexcept {
    return array.FoldL(init, f);
  }

};

}
