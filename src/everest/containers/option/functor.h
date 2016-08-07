#pragma once

#include <everest/containers/option.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Functor<Option<T>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static Option<B> Map(F f, const Option<T>& option) noexcept {
    return option.Map(f);
  }

};

}
