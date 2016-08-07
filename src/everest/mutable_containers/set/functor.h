#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class Functor<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static MutableSet<B> Map(F f, const MutableSet<T>& set) noexcept {
    return set.Map(f);
  }

};

}