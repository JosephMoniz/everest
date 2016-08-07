#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class Functor<Vector<T>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static Vector<B> Map(F f, const Vector<T>& vector) noexcept {
    return vector.Map(f);
  }

};

}