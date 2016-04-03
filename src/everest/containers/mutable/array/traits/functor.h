#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template<class T, size_t S>
class Functor<MutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static SharedArray <B, S> Map(F f, const MutableArray<T, S>& array) noexcept {
    auto newArray = MakeSharedArray<B, S>();
    for (size_t i = 0; i < S; i++) {
      newArray->_array[i] = f(array.Pointer()[i]);
    }
    return newArray;
  }

};

}
