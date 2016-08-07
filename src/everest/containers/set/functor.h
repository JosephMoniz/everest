#pragma once

#include <everest/containers/set.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template <class T>
class Set;

template<class T>
class Functor<Set<T>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static Set<B> Map(F f, const Set<T>& set) noexcept {
    return set.Map(f);
  }

};

}