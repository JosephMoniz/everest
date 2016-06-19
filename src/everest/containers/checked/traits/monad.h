#pragma once

#include <everest/meta/nth_arg.h>
#include <everest/containers/checked.h>
#include <everest/traits/lawful/monad.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Monad<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = nth_arg<typename std::result_of<F(T)>::type, 1>>
  static constexpr Checked<E, B> FlatMap(F f, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return Error<E, B>(error); },
      [&](const T& ok)    { return f(ok); }
    );
  }

  template <class B>
  static constexpr Checked<E, B> Then(const Checked<E, T>& m, const Checked<E, B>& n) noexcept {
    return Match(m,
      [&](const E& error) { return m; },
      [&](const T& ok)    { return n; }
    );
  }

};

}