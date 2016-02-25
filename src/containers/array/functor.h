#ifndef TRAITOROUS_CONTAINERS_ARRAY_FUNCTOR_H
#define TRAITOROUS_CONTAINERS_ARRAY_FUNCTOR_H

#include "containers/array.h"
#include "traits/lawful/functor.h"

namespace traitorous {

template<class T, size_t S>
using Array = Shared<LocalArray<T, S>>;

template<class T, size_t S>
class Functor<Array<T, S>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr Array<B, S> Map(F f, const Array<T, S>& array) noexcept {
    return Functor<LocalArray<T, S>>::Map(f, *array.Pointer());
  }

};

}

#endif
