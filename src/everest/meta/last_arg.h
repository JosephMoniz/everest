#pragma once

namespace everest {

template <class>
struct last_arg;

template <template <class...> class T, class X, class ...Xs>
struct last_arg<T<X, Xs...>> {
  using type = last_arg<Xs...>;
};

template <template <class> class T, class X>
struct last_arg<T<X>> {
  using type = X;
};

}
