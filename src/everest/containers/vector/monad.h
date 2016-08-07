#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/lawful/monad.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class Monad<Vector<T>> final {
public:

  static constexpr bool exists = true;

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static Vector<B> FlatMap(F f, const Vector<T>& vector) noexcept {
    return vector.FlatMap(f);
  }

  template <class B>
  static Vector<B> Then(const Vector<T>& first, const Vector<B>& second) noexcept {
    return first.Then(second);
  }

};

}