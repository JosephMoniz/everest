#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_FOLDABLE_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_FOLDABLE_H

#include "containers/option.h"
#include "traits/lawful/foldable.h"
#include "traits/lawful/monoid.h"

namespace traitorous {

template <class T>
class LocalOption;

template <class T>
class Foldable<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const LocalOption<T>& n) noexcept {
    return Match(n,
      []()             { return ZeroVal<T>::Zero(); },
      [&n](const T& m) { return m; }
    );
  }

  template <class Fn,
            class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const LocalOption<T>& n) noexcept {
    return Match(n,
      []()             { return ZeroVal<M>::Zero(); },
      [&f](const T& m) { return f(m); }
    );
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const LocalOption<T>& n) noexcept
  {
    return Match(n,
      [&]()           { return init; },
      [&](const T& m) { return f(init, m); }
    );
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const LocalOption<T>& n) noexcept
  {
    return Match(n,
      [&]()           { return init; },
      [&](const T& m) { return f(init, m); }
    );
  }

};

}

#endif
