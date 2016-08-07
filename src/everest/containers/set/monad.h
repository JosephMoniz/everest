#pragma once

#include <everest/containers/set.h>
#include <everest/traits/lawful/monad.h>

namespace everest {

template <class T>
class Set;

template<class T>
class Monad<Set<T>> final {
public:

  static constexpr bool exists = true;

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static Set<B> FlatMap(F f, const Set<T>& set) noexcept {
    return set.FlatMap(f);
  }

  template <class B>
  static Set<B> Then(const Set<T>& first, const Set<B>& second) noexcept {
    return first.Then(second);
  }

};

}