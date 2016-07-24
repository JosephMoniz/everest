#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/lawful/foldable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Foldable<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static T Fold(const MutableVector<T>& vector) noexcept {
    return vector.Fold();
  }

  template <class Fn,
    class M = typename std::result_of<Fn(T)>::type>
  static M FoldMap(Fn f, const MutableVector<T>& vector) noexcept {
    return vector.FoldMap(f);
  }

  template <class Fn, class B>
  static B FoldR(Fn f, const B& init, const MutableVector<T>& vector) noexcept {
    return vector.FoldR(init, f);
  }

  template <class Fn, class B>
  static B FoldL(Fn f, const B& init, const MutableVector<T>& vector) noexcept {
    return vector.FoldL(init, f);
  }

};

}