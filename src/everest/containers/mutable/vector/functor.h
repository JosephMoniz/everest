#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class Functor<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static MutableVector<B> Map(F f, const MutableVector<T>& vector) noexcept {
    auto result = MutableVector<B>(Length(vector));
    ForEach(vector, [&](const T& item) {
      PushInPlace(f(item), result);
    });
    return result;
  }

};

}