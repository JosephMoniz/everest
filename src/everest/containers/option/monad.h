#pragma once

#include <everest/containers/option.h>
#include <everest/traits/lawful/monad.h>
#include <everest/meta/nth_arg.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Monad<Option<T>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static Option<B> FlatMap(F f, const Option<T>& option) noexcept {
    return option.FlatMap(f);
  }

  template <class B>
  static Option<B> Then(const Option<T>& first, const Option<B>& second) noexcept {
    return first.Then(second);
  }

};

}
