#pragma once

#include <meta/nth_arg.h>
#include "containers/option.h"
#include "traits/lawful/monad.h"

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class Monad<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = nth_arg<nth_arg<typename std::result_of<F(T)>::type, 0>, 0>>
  static constexpr SharedOption<B> FlatMap(F f, const SharedOption<T>& m) noexcept {
    return Match(m,
      [&m]()           { return SharedNone<B>(); },
      [&f](const T& t) { return f(t); }
    );
  }

  template <class B>
  static constexpr SharedOption<B> Then(const SharedOption<T>& m, const SharedOption<B>& n) noexcept {
    return Match(m,
      []()        { return SharedNone<B>(); },
      [&](auto _) { return n; }
    );
  }

};


}
