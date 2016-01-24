#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_MONAD_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_MONAD_H

#include "containers/local_option.h"
#include "traits/lawful/monoid.h"

namespace traitorous {

template <class T>
class monad<local_option, T> {
public:

  static constexpr bool exists = true;

  template <class F,
            class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr local_option<B> flat_map(F f, const local_option<T>& m) noexcept {
    return match(m,
      [&m]()           { return local_none<B>(); },
      [&f](const T& t) { return f(t); }
    );
  }

  template <class B>
  static constexpr local_option<B> then(const local_option<T>& m,
                                        const local_option<B>& n) noexcept
  {
    return match(m,
      []()        { return local_none<B>(); },
      [&](auto _) { return n; }
    );
  }

};

}

#endif
