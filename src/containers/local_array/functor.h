#ifndef TRAITOROUS_CONTAINERS_LOCAL_ARRAY_FUNCTOR_H
#define TRAITOROUS_CONTAINERS_LOCAL_ARRAY_FUNCTOR_H

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/lawful/functor.h"

namespace traitorous {

template <class T, size_t S>
class LocalArray;

template<class T, size_t S>
class Functor<LocalArray<T, S>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr Array<B, S> Map(F f, const LocalArray<T, S>& array) noexcept {
    auto newArray = MakeArray<B, S>();
    for (size_t i = 0; i < S; i++) {
      newArray->_array[i] = f(array.Pointer()[i]);
    }
    return newArray;
  }

};

}

#endif
