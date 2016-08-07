#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/lawful/monad.h>

namespace everest {

template<class T>
class MutableSet;

template<class T>
class Monad<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static MutableSet<B> FlatMap(F f, const MutableSet<T>& set) noexcept {
    return set.FlatMap(f);
  }

  template <class B>
  static MutableSet<B> Then(const MutableSet<T>& first, const MutableSet<B>& second) noexcept {
    return first.Then(second);
  }

};

}