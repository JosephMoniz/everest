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
  static constexpr Option<B> Map(F f, const Option<T>& n) noexcept {
    return Match(n,
      []()             { return None<B>(); },
      [&f](const T& m) { return Some<B>(f(m)); }
    );
  }

};

}
