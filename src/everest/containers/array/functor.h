#pragma once

#include <everest/containers/array.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template <class T, size_t S>
class Array;

template<class T, size_t S>
class Functor<Array<T, S>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static Array<B, S> Map(F f, const Array<T, S>& array) noexcept {
    return array.Map(f);
  }

};

}
