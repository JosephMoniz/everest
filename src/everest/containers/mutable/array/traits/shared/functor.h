#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/lawful/functor.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
using SharedArray = Shared<MutableArray<T, S>>;

template<class T, size_t S>
class Functor<SharedArray<T, S>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static SharedArray<B, S> Map(F f, const SharedArray<T, S>& array) noexcept {
    return Functor<MutableArray<T, S>>::Map(f, *array.Pointer());
  }

};

}
