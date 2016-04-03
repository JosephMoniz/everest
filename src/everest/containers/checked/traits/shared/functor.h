#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template <class E, class T>
class Functor<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr SharedChecked<E, B> Map(F f, const SharedChecked<E, T>& checked) noexcept {
    return Match(checked,
      [&](const E& error) { return MakeSharedError<E, B>(error); },
      [&](const T& ok)    { return MakeSharedOk<E, B>(f(ok)); }
    );
  }

};

}