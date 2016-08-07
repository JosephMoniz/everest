#pragma once

#include <everest/mutable_containers/mutable_array.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template<class T, size_t S>
class Functor<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static MutableArray<B, S> Map(F f, const MutableArray<T, S>& array) noexcept {
    return array.Map(f);
  }

};

}
