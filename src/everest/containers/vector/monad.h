#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/lawful/monad.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class Monad<Vector<T>> {
public:

  static constexpr bool exists = true;

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr Vector<B> FlatMap(F f, const Vector<T>& vector) noexcept {
    return Monad<MutableVector<T>>::FlatMap(f, vector._wrapped);
  }

  template <class B>
  static constexpr Vector<B> Then(const Vector<T>& first, const Vector<B>& second) noexcept {
    return second;
  }

};

}