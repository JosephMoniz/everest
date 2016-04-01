#pragma once

#include <everest/containers/array.h>
#include <everest/traits/lawful/functor.h>
#include <everest/containers/shared.h>

namespace traitorous {

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template<class T, size_t S>
class Functor<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static SharedArray<B, S> Map(F f, const SharedArray<T, S>& array) noexcept {
    return Functor<Array<T, S>>::Map(f, *array.Pointer());
  }

};

}
