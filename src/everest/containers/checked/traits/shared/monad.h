#pragma once

#include <everest/meta/nth_arg.h>
#include <everest/containers/checked.h>
#include <everest/traits/lawful/monad.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template <class E, class T>
class Monad<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = nth_arg<nth_arg<typename std::result_of<F(T)>::type, 0>, 1>>
  static constexpr SharedChecked<E, B> FlatMap(F f, const SharedChecked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return MakeSharedError<E, B>(error); },
      [&](const T& ok)    { return f(ok); }
    );
  }

  template <class B>
  static constexpr SharedChecked<E, B> Then(const SharedChecked<E, T>& m, const SharedChecked<E, B>& n) noexcept {
    return Match(m,
      [&](const E& error) { return m; },
      [&](const T& ok)    { return n; }
    );
  }

};

}