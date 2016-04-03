#pragma once

#include <everest/containers/option.h>
#include <everest/containers/shared.h>

namespace everest {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class Functor<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr SharedOption<B> Map(F f, const SharedOption<T>& n) noexcept {
    return Match(n,
      []()             { return SharedNone<B>(); },
      [&f](const T& m) { return SharedSome<B>(f(m)); }
    );
  }

};

}
