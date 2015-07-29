#ifndef TRAITOROUS_CONTAINERS_VALIDATION
#define TRAITOROUS_CONTAINERS_VALIDATION 1

#include <string>
#include <type_traits>

#include "core/tagged_union.h"

#include "containers/identity.h"

#include "traits/alternative.h"
#include "traits/applicative.h"
#include "traits/eq.h"
#include "traits/functor.h"
#include "traits/monad.h"
#include "traits/show.h"

namespace traitorous {

template <class F, class S>
class validation;

template<typename T>
using _failure = identity_t<T>;

template<typename T>
using _success = identity_t<T>;

template <class F,
          class S,
          class Ff,
          class Sf,
          class R = typename std::result_of<Ff(F)>::type>
static constexpr R cata(const validation<F, S>& v, Ff f, Sf s) noexcept {
  return (typeid(v) == typeid(_failure<F>)) ? f(v.template get<F>()) : s(v.template get<S>());
}

template<class F, class S>
class validation : public tagged_union<_success<S>, _failure<F>> {
public:

  validation(const S& s):
    tagged_union<_success<S>, _failure<F>>(_success<S>(s)) {}

  validation(const F& f):
    tagged_union<_success<S>, _failure<F>>(typeid(_failure<F>).hash_code(),
                                           std::addressof(f)) {}

  validation(const validation<F, S>& val):
    tagged_union<_success<S>, _failure<F>>(val) {}

  validation(const validation<F, S>&& val):
    tagged_union<_success<S>, _failure<F>>(val) {}

  template <class Ff, class Sf, class R = typename std::result_of<Ff(F)>::type>
  constexpr inline R cata(Ff f, Sf s) const noexcept {
    return traitorous::cata(*this, f, s);
  }

};

template <class F, class S>
validation<F, S> success(const S& s) {
  return validation<F, S>(s);
}

template <class F, class S>
validation<F, S> failure(const F& f) {
  return validation<F, S>(f);
}

template <class F, class S>
struct eq<validation<F, S>> {
  static constexpr bool equals(const validation<F, S>& lhs,
                               const validation<F, S>& rhs) noexcept
  {
    return lhs.cata(
      [&rhs](const F& f1) {
        return rhs.cata(
          [&f1](const F& f2) { return f1 == f2; },
          [](const S& s) { return false; }
        );
      },
      [&rhs](const S& s1) {
        return rhs.cata(
          [](const F& f) { return false; },
          [&s1](const S& s2) { return s1 == s2; }
        );
      }
    );
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct functor<validation<F, S>> {
  template <class Fn, class B = typename std::result_of<Fn(S)>::type>
  static constexpr validation<F, B> map(Fn f, const validation<F, S>& v) noexcept {
    return v.cata(
      [&v](const F& e) { return failure(e); },
      [&f](const S& s) { return success(f(s)); }
    );
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct applicative<validation<F, S>> {
  template <class A, class B = typename std::result_of<S(A)>::type>
  static constexpr validation<F, B> ap(const validation<F, S>& f,
                                       const validation<F, A>& v) noexcept
  {
    return f >>= [&v](const S& fn) { return v.map(fn); };
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct alternative<validation<F, S>> {
  static constexpr validation<F, S> alt(const validation<F, S>& a,
                                        const validation<F, S>& b) noexcept
  {
    return a.cata(
      [&b](const F& f) { return b; },
      [&a](const S& s) { return a; }
    );
  }
};

template <class F, class S>
struct monad<validation<F, S>> {
  template <class Fn, class B = nth_arg<typename std::result_of<Fn(S)>::type, 1>>
  static constexpr validation<F, B> flat_map(Fn f, const validation<F, S>& v) noexcept {
    return v.cata(
      [](const F& e) { return failure(e); },
      [&f](const S& s) { return f(s); }
    );
  }
  static constexpr validation<F, S> then(const validation<F, S>& a,
                                         const validation<F, S>& b) noexcept
  {
    return b;
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct shows<validation<F, S>> {
  static const std::string show(const validation<F, S>& v) noexcept {
    return v.cata(
      [](const F& f) { return std::string("failure(") + shows<F>::show(f) + ")"; },
      [](const S& s) { return std::string("success(") + shows<S>::show(s) + ")"; }
    );
  }
  static constexpr bool exists = true;
};

}

#endif
