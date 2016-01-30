#ifndef TRAITOROUS_CONTAINERS_OPTION_FOLDABLE_H
#define TRAITOROUS_CONTAINERS_OPTION_FOLDABLE_H

#include "containers/option.h"
#include "traits/lawful/foldable.h"

namespace traitorous {

template <class T>
class Foldable<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const Option<T>& n) noexcept {
    return Match(n,
      []()             { return ZeroVal<T>::Zero(); },
      [&n](const T& m) { return m; }
    );
  }

  template <class Fn,
            class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const Option<T>& n) noexcept {
    return Match(n,
      []()             { return ZeroVal<M>::Zero(); },
      [&f](const T& m) { return f(m); }
    );
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const Option<T>& n) noexcept
  {
    return Match(n,
      [&]()           { return init; },
      [&](const T& m) { return f(init, m); }
    );
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const Option<T>& n) noexcept
  {
    return Match(n,
      [&]()           { return init; },
      [&](const T& m) { return f(init, m); }
    );
  }

};


}

#endif
