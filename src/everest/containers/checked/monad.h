#pragma once

#include <everest/meta/nth_type_arg.h>
#include <everest/containers/checked.h>
#include <everest/traits/lawful/monad.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Monad<Checked<E, T>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = nth_type_arg<typename std::result_of<F(T)>::type, 1>>
  static Checked<E, B> FlatMap(F f, const Checked<E, T>& checked) noexcept {
    return checked.FlatMap(f);
  }

  template <class B>
  static const Checked<E, B>& Then(const Checked<E, T>& checked, const Checked<E, B>& other) noexcept {
    return checked.Then(other);
  }

};

}