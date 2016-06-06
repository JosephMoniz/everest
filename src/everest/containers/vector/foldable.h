#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/lawful/foldable.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Foldable<Vector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const Vector<T>& vector) noexcept {
    return Foldable<MutableVector<T>>::Fold(vector._wrapped);
  }

  template <class Fn,
            class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const Vector<T>& vector) noexcept {
    return Foldable<MutableVector<T>>::FoldMap(f, vector._wrapped);
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const Vector<T>& vector) noexcept
  {
    return Foldable<MutableVector<T>>::FoldR(f, init, vector._wrapped);
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const Vector<T>& vector) noexcept
  {
    return Foldable<MutableVector<T>>::FoldL(f, init, vector._wrapped);
  }

};

}