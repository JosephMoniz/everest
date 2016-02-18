#ifndef TRAITOROUS_CONTAINERS_OPTION_FUNCTOR_H
#define TRAITOROUS_CONTAINERS_OPTION_FUNCTOR_H

#include "containers/option.h"
#include "traits/lawful/functor.h"

namespace traitorous {

template <class T>
class Functor<Option<T>> {
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

#endif
