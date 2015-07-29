#ifndef TRAITOROUS_CONTAINERS_VALIDATION_H
#define TRAITOROUS_CONTAINERS_VALIDATION_H

#include <type_traits>
#include <functional>
#include <string>
#include <memory>

#include "meta/nth_arg.h"

#include "meta/max.h"

#include "traits/containable.h"
#include "traits/container.h"
#include "traits/eq.h"
#include "traits/hashable.h"
#include "traits/zero.h"
#include "traits/semigroup.h"
#include "traits/monoid.h"
#include "traits/filterable.h"
#include "traits/ord.h"
#include "traits/functor.h"
#include "traits/applicative.h"
#include "traits/alternative.h"
#include "traits/monad.h"
#include "traits/monad_plus.h"
#include "traits/foldable.h"
#include "traits/unwrappable.h"

namespace traitorous {

using std::shared_ptr;

enum validation_type {
  VALIDATION_FAILURE,
  VALIDATION_SUCCESS
};

template<class F, class S>
class validation {

  using data_t = typename std::aligned_storage<
    meta_max<sizeof(F), sizeof(S)>::value,
    meta_max<alignof(F), alignof(S)>::value
  >::type;
  const validation_type _tag;
  data_t _value;

public:

  validation(validation_type t, const F& o) : _tag(t) {
    new(&_value) F(o);
  }

  template<class F1 = F,
           class S1 = S,
           class = typename std::enable_if<!std::is_same<F1, S1>::value>::type>
  validation(validation_type t, const S& o) : _tag(t) {
    new(&_value) S(o);
  }

  ~validation() noexcept {
    if (_tag == VALIDATION_FAILURE) {
      reinterpret_cast<F *>(&_value)->~F();
    } else {
      reinterpret_cast<S *>(&_value)->~S();
    }
  }

  validation_type get_type() const {
    return _tag;
  };

  const F &get_failure() const {
    return *reinterpret_cast<const F *>(&_value);
  }

  const S &get_success() const {
    return *reinterpret_cast<const S *>(&_value);
  }

};

template<class F, class S>
const validation<F, S> failure(const F &o) {
  return validation<F, S>(VALIDATION_FAILURE, o);
}

template<class F, class S>
const validation<F, S> success(const S &o) {
  return validation<F, S>(VALIDATION_SUCCESS, o);
}

template <class F,
          class S,
          class Ff,
          class Fs,
          class R = typename std::result_of<Ff(F)>::type>
static constexpr R match(const validation<F, S>& o, Ff f, Fs s) noexcept {
  return (o.get_type() == VALIDATION_FAILURE)
         ? f(o.get_failure())
         : s(o.get_success());
}

template <class F,
          class S,
          class Ff,
          class Fs,
          class R = typename std::result_of<Ff(F)>::type>
static constexpr R match(shared_ptr<validation<F, S>> o, Ff f, Fs s) noexcept {
  return match(*o, f, s);
}

template <class F, class S>
struct containable<validation<F, S>> {
  static constexpr bool contains(const S& n, const validation<F, S>& v) noexcept {
    return match(v,
      [](auto f)   { return false; },
      [&n](auto s) { return n == s; }
    );
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct container<validation<F, S>> {
  static constexpr size_t length(const validation<F, S>& o) noexcept {
    return match(o,
      [](auto f) { return 0; },
      [](auto s) { return 1; }
    );
  }
  static constexpr bool is_empty(const validation<F, S>& o) noexcept {
    return match(o,
      [](auto f) { return true; },
      [](auto s) { return false; }
    );
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct eq<validation<F, S>> {
  static constexpr bool equals(const validation<F, S>& lhs,
                               const validation<F, S>& rhs) noexcept
  {
    return match(lhs,
      [&](auto x){
        return match(rhs,
          [&](auto y) { return x == y; },
          [](auto _)  { return false; }
        );
      },
      [&](auto x){
        return match(rhs,
          [](auto _)  { return false; },
          [&](auto y) { return x == y; }
        );
      }
    );
  }
  static constexpr bool exists = true;
};

template <class F, class S>
constexpr inline bool operator==(const validation<F, S>& lhs, const validation<F, S>& rhs) noexcept {
  return eq<validation<F, S>>::equals(lhs, rhs);
}

template <class F, class S>
constexpr inline bool operator!=(const validation<F, S>& lhs, const validation<F, S>& rhs) noexcept {
  return !eq<validation<F, S>>::equals(lhs, rhs);
}

template <class F, class S>
struct zero_val<validation<F, S>> {
  static constexpr validation<F, S> zero() { return success<F, S>(zero_val<S>::zero()); }
  static constexpr bool exists = true;
};


template <class F, class S>
struct semigroup<validation<F, S>> {
  static constexpr validation<F, S> add(const validation<F, S>& lhs,
                                        const validation<F, S>& rhs) noexcept
  {
    return match(lhs,
      [&](auto x) {
        return match(rhs,
          [&](auto y) { return failure<F, S>(x + y); },
          [&](auto y) { return lhs; }
        );
      },
      [&](auto x) {
        return match(rhs,
          [&](auto y) { return rhs; },
          [&](auto y) { return success<F, S>(x + y); }
        );
      }
    );
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct monoid<validation<F, S>> {
  static constexpr bool exists = true;
};

template <class F, class S>
struct filterable<validation<F, S>> {
  template <class P>
  static constexpr validation<F, S> filter(P p, const validation<F, S>& n) noexcept {
    return match(n,
      [&](auto _) { return n; },
      [&](auto s) { return p(s) ? n : zero<validation<F, S>>(); }
    );
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct ord<validation<F, S>> {

  static constexpr Ordering cmp(const validation<F, S>& lhs,
                                const validation<F, S>& rhs) noexcept
  {
    return match(lhs,
      [&](auto x) {
        return match(rhs,
          [&](auto y) { return ord<F>::cmp(x, y); },
          [](auto y)  { return LESS; }
        );
      },
      [&](auto x) {
        return match(rhs,
          [](auto y)  { return GREATER; },
          [&](auto y) { return ord<S>::cmp(x, y); }
        );
      }
    );
  }

  static constexpr const validation<F, S>& min(const validation<F, S>& lhs,
                                               const validation<F, S>& rhs) noexcept
  {
    return (ord<validation<F, S>>::cmp(lhs, rhs) == GREATER) ? rhs : lhs;
  }
  static constexpr const validation<F, S>& max(const validation<F, S>& lhs,
                                               const validation<F, S>& rhs) noexcept
  {
    return (ord<validation<F, S>>::cmp(lhs, rhs) == LESS) ? rhs : lhs;
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct functor<validation<F, S>> {
  template <class Fn, class B = typename std::result_of<Fn(S)>::type>
  static constexpr validation<F, B> map(Fn f, const validation<F, S>& n) noexcept {
    return match(n,
      [&](auto _)  { return n; },
      [&f](auto s) { return success<F, B>(f(s)); }
    );
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct applicative<validation<F, S>> {
  template <class Fn, class B = typename std::result_of<Fn(S)>::type>
  static constexpr validation<F, B> ap(const validation<F, Fn>& f,
                                       const validation<F, S>& a) noexcept
  {
    return flat_map([&](auto fn) { return map(fn, a); }, f);
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct alternative<validation<F, S>> {
  static constexpr validation<F, S> alt(const validation<F, S>& lhs,
                                        const validation<F, S>& rhs) noexcept
  {
    return match(lhs,
      [&](auto f) { return rhs; },
      [&](auto s) { return lhs; }
    );
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct monad<validation<F, S>> {
  template <class Fn,
            class B = nth_arg<typename std::result_of<Fn(S)>::type, 1>>
  static constexpr validation<F, B> flat_map(Fn f, const validation<F, S>& m) noexcept {
    return match(m,
      [&](auto _) { return m; },
      [&](auto n) { return f(n); }
    );
  }
  template <class B>
  static constexpr validation<F, B> then(const validation<F, S>& m,
                                         const validation<F, B>& n) noexcept
  {
    return match(m,
      [&](auto _) { return m; },
      [&](auto _) { return n; }
    );
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct monad_plus<validation<F, S>> {
  static constexpr validation<F, S> mplus(const validation<F, S>& lhs,
                                          const validation<F, S>& rhs) noexcept
  {
    return match(lhs,
      [&rhs](auto _) { return rhs; },
      [&lhs](auto _) { return lhs; }
    );
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct foldable<validation<F, S>> {
  static constexpr S fold(const validation<F, S>& n) noexcept {
    return match(n,
      [](auto _)  { return zero_val<S>::zero(); },
      [&](auto m) { return m; }
    );
  }
  template <class Fn,
            class M = typename std::result_of<Fn(S)>::type>
  static constexpr M fold_map(Fn f, const validation<F, S>& n) noexcept {
    return match(n,
      [](auto _)  { return zero_val<M>::zero(); },
      [&](auto m) { return f(m); }
    );
  }
  template <class Fn, class B>
  static constexpr B foldr(Fn f,
                           const B& init,
                           const validation<F, S>& n) noexcept
  {
    return match(n,
      [&](auto _) { return init; },
      [&](auto m) { return f(init, m); }
    );
  }
  template <class Fn, class B>
  static constexpr B foldl(Fn f,
                           const B& init,
                           const validation<F, S>& n) noexcept
  {
    return match(n,
      [&](auto _) { return init; },
      [&](auto m) { return f(init, m); }
    );
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct unwrappable<validation<F, S>> {
  template <class D>
  static constexpr S get_or_else(D d, const validation<F, S>& f) noexcept {
    return match(f,
      [&](auto _) { return d(); },
      [](auto m)  { return m; }
    );
  }
  static constexpr S get_or_default(const S& d, const validation<F, S>& n) noexcept {
    return match(n,
      [&](auto _) { return d; },
      [](auto m)  { return m; }
    );
  }
  static constexpr bool exists = true;
};

template <class F, class S>
struct shows<validation<F, S>> {
  static const std::string show(const validation<F, S>& n) noexcept {
    return match(n,
      [](auto f) { return std::string("failure(") + shows<F>::show(f) + ")"; },
      [](auto s) { return std::string("success(") + shows<S>::show(s) + ")"; }
    );
  }
  static constexpr bool exists = true;
};


}

#endif
