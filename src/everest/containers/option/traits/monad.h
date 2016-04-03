#pragma once

#include <everest/containers/option.h>
#include <everest/traits/lawful/monad.h>
#include <everest/meta/nth_arg.h>

namespace everest {

template <class T>
class Option;

template <class T>
class Monad<Option<T>> {
public:

  static constexpr bool exists = true;

  template <class F,
            class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr Option<B> FlatMap(F f, const Option<T>& m) noexcept {
    return Match(m,
      [&m]()           { return None<B>(); },
      [&f](const T& t) { return f(t); }
    );
  }

  template <class B>
  static constexpr Option<B> Then(const Option<T>& m,
                                  const Option<B>& n) noexcept
  {
    return Match(m,
      []()        { return None<B>(); },
      [&](auto _) { return n; }
    );
  }

};

}
