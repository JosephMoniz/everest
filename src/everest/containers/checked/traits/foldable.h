#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/foldable.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Foldable<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [](const E& error) { return ZeroVal<T>::Zero(); },
      [&](const T& ok)   { return ok; }
    );
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [](const E& error) { return ZeroVal<M>::Zero(); },
      [&](const T& ok)   { return f(ok); }
    );
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f, const B& init, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return init; },
      [&](const T& ok)    { return f(init, ok); }
    );
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f, const B& init, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return init; },
      [&](const T& ok)    { return f(init, ok); }
    );
  }

};

}