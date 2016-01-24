#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_FOLDABLE_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_FOLDABLE_H

#include "containers/local_option.h"
#include "traits/lawful/foldable.h"
#include "traits/lawful/monoid.h"

namespace traitorous {

template <class T>
class foldable<local_option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr T fold(const local_option<T>& n) noexcept {
    return match(n,
      []()             { return zero_val<T>::zero(); },
      [&n](const T& m) { return m; }
    );
  }

  template <class Fn,
            class M = typename std::result_of<Fn(T)>::type>
  static constexpr M fold_map(Fn f, const local_option<T>& n) noexcept {
    return match(n,
      []()             { return zero_val<M>::zero(); },
      [&f](const T& m) { return f(m); }
    );
  }

  template <class Fn, class B>
  static constexpr B foldr(Fn f,
                           const B& init,
                           const local_option<T>& n) noexcept
  {
    return match(n,
      [&]()           { return init; },
      [&](const T& m) { return f(init, m); }
    );
  }

  template <class Fn, class B>
  static constexpr B foldl(Fn f,
                           const B& init,
                           const local_option<T>& n) noexcept
  {
    return match(n,
      [&]()           { return init; },
      [&](const T& m) { return f(init, m); }
    );
  }

};

}

#endif
