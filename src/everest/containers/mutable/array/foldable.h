#pragma once

#include <everest/traits/lawful/foldable.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/containers/mutable/mutable_array.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template <class T, size_t S>
class Foldable<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  static T Fold(const MutableArray<T, S>& array) noexcept {
    return array.Fold();
  }

  template <class Fn,
    class M = typename std::result_of<Fn(T)>::type>
  static M FoldMap(Fn f, const MutableArray<T, S>& array) noexcept {
    return array.FoldMap(f);
  }

  template <class Fn, class B>
  static B FoldR(Fn f, const B& init, const MutableArray<T, S>& array) noexcept {
    return array.FoldR(init, f);
  }

  template <class Fn, class B>
  static B FoldL(Fn f, const B& init, const MutableArray<T, S>& array) noexcept {
    return array.FoldL(init, f);
  }

};

}
