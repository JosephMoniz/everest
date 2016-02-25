#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_FUNCTOR_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_FUNCTOR_H

#include "containers/option.h"
#include "traits/lawful/functor.h"

namespace traitorous {

template <class T>
class LocalOption;

template <class T>
class Functor<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr LocalOption<B> Map(F f, const LocalOption<T>& n) noexcept {
    return Match(n,
      []()             { return LocalNone<B>(); },
      [&f](const T& m) { return LocalSome<B>(f(m)); }
    );
  }

};

}

#endif
