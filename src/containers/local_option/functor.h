#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_FUNCTOR_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_FUNCTOR_H

#include "containers/local_option.h"
#include "traits/lawful/functor.h"

namespace traitorous {

template <class T>
class functor<local_option, T> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr local_option<B> map(F f, const local_option<T>& n) noexcept {
    return match(n,
      []()             { return local_none<B>(); },
      [&f](const T& m) { return local_some<B>(f(m)); }
    );
  }

};

}

#endif
