#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/lawful/monad.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class Monad<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr MutableVector<B> FlatMap(F f, const MutableVector<T>& vector) noexcept {
    return vector.FlatMap(f);
  }

  template <class B>
  static constexpr MutableVector<B> Then(const MutableVector<T>& first, const MutableVector<B>& second) noexcept {
    return first.Then(second);
  }

};

}