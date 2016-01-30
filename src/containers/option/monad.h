#ifndef TRAITOROUS_CONTAINERS_OPTION_MONAD_H
#define TRAITOROUS_CONTAINERS_OPTION_MONAD_H

#include "containers/option.h"
#include "traits/lawful/monad.h"

namespace traitorous {

template <class T>
class Monad<Option, T> {
public:

  static constexpr bool exists = true;

  template <class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr Option<B> FlatMap(F f, const Option<T>& m) noexcept {
    return Match(m,
      [&m]()           { return NOne<B>(); },
      [&f](const T& t) { return f(t); }
    );
  }

  template <class B>
  static constexpr Option<B> Then(const Option<T>& m, const Option<B>& n) noexcept {
    return Match(m,
      []()        { return NOne<B>(); },
      [&](auto _) { return n; }
    );
  }

};


}

#endif
