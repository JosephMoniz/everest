#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/lawful/foldable.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Foldable<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static T Fold(const Vector<T>& vector) noexcept {
    return vector.Fold();
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  static M FoldMap(Fn f, const Vector<T>& vector) noexcept {
    return vector.FoldMap(f);
  }

  template <class Fn, class B>
  static B FoldR(Fn f, const B& init, const Vector<T>& vector) noexcept {
    return vector.FoldR(init, f);
  }

  template <class Fn, class B>
  static B FoldL(Fn f, const B& init, const Vector<T>& vector) noexcept {
    return vector.FoldL(init, f);
  }

};

}