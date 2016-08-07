#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Functor<Checked<E, T>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static Checked<E, B> Map(F f, const Checked<E, T>& checked) noexcept {
    return checked.Map(f);
  }

};

}