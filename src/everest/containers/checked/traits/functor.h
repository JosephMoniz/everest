#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Functor<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr Checked<E, B> Map(F f, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return Error<E, B>(error); },
      [&](const T& ok)    { return Ok<E, B>(f(ok)); }
    );
  }

};

}