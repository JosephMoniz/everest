#pragma once

#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/foldable.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/containers/option.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Foldable<Option<T>> final {
public:

  static constexpr bool exists = true;

  static T Fold(const Option<T>& option) noexcept {
    return option.Fold();
  }

  template <class Fn,
    class M = typename std::result_of<Fn(T)>::type>
  static M FoldMap(Fn f, const Option<T>& option) noexcept {
    return option.FoldMap(f);
  }

  template <class Fn, class B>
  static B FoldR(Fn f, const B& init, const Option<T>& option) noexcept {
    return option.FoldR(init, f);
  }

  template <class Fn, class B>
  static B FoldL(Fn f, const B& init, const Option<T>& option) noexcept {
    return option.FoldL(init, f);
  }

};

}
