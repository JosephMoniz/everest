#pragma once

#include <everest/mutable_containers/mutable_vector.h>
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
    return vector.Map(f);
  }

};

}