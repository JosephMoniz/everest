#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/lawful/functor.h>
#include <everest/memory/shared.h>

namespace everest {

template<class T, size_t S>
using SharedMutableArray = Shared<MutableArray<T, S>>;

template<class T, size_t S>
class Functor<SharedMutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static SharedMutableArray<B, S> Map(F f, const SharedMutableArray<T, S>& array) noexcept {
    return Functor<MutableArray<T, S>>::Map(f, *array);
  }

};

}
