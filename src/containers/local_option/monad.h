#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_MONAD_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_MONAD_H

#include "containers/local_option.h"
#include "traits/lawful/monad.h"
#include "meta/nth_arg.h"

namespace traitorous {

template <class T>
class Monad<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  template <class F,
            class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr LocalOption<B> FlatMap(F f, const LocalOption<T>& m) noexcept {
    return Match(m,
      [&m]()           { return LocalNone<B>(); },
      [&f](const T& t) { return f(t); }
    );
  }

  template <class B>
  static constexpr LocalOption<B> Then(const LocalOption<T>& m,
                                       const LocalOption<B>& n) noexcept
  {
    return Match(m,
      []()        { return LocalNone<B>(); },
      [&](auto _) { return n; }
    );
  }

};

}

#endif
