#ifndef TRAITOROUS_CONTAINERS_OPTION
#define TRAITOROUS_CONTAINERS_OPTION 1

#include <string>

#include "core/tagged_union.h"

#include "traits/catamorphism.h"
#include "traits/functor.h"
#include "traits/show.h"

struct none {} none_instance;

struct some_ {} some;

template <class T>
using option = tagged_union<T, none>;

template <class T>
struct catamorphism<option<T>> {
  template <class R>
  static constexpr R cata(const option<T>& o,
                          std::function<R()> n,
                          std::function<R(const T&)> s)
  {
    return (o.template is<none>()) ? n() : s(o.template get<T>());
  }
  static constexpr bool exists = true;
};

template <class T>
struct functor<option<T>> {
  template <class R>
  static constexpr option<R> map(const option<T>& n, std::function<R(const T&)> f) {
    return catamorphism<option<T>>::cata<option<R>>(n,
      []() { auto n = option<R>(); n.template set<none>(none_instance); return n; },
      [f](const T& n) { return option<R>(f(n)); }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct shows<option<T>> {
  static const std::string show(const option<T>& n) {
    return catamorphism<option<T>>::cata<std::string>(n,
      []() { return std::string("None"); },
      [](const T& n) { return std::string("Some(") + shows<T>::show(n) + ")"; }
    );
  }
  static constexpr bool exists = true;
};

#endif
