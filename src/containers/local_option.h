#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_H
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_H

#include <type_traits>
#include <functional>
#include <string>
#include <memory>

#include "meta/nth_arg.h"

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

enum option_type {
  OPTION_SOME,
  OPTION_NONE
};

template<class T>
class local_option {

  using data_t = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
  const option_type _tag;
  data_t _value;

public:

  local_option() : _tag(OPTION_NONE) {}

  local_option(const T& o) : _tag(OPTION_SOME) {
    new (&_value) T(o);
  }

  ~local_option() noexcept {
    if (_tag == OPTION_SOME) {
      reinterpret_cast<T*>(&_value)->~T();
    }
  }

  option_type get_type() const {
    return _tag;
  };

  const T& get() const {
    return *reinterpret_cast<const T*>(&_value);
  }

};

template<class T>
const local_option<T> local_some(const T &o) {
  return local_option<T>(o);
}

template<class T>
const local_option<T> local_none() {
  return local_option<T>();
}

template <class T,
          class N,
          class S,
          class R = typename std::result_of<N()>::type>
static constexpr R match(const local_option<T>& o, N n, S s) noexcept {
  return (o.get_type() == OPTION_NONE)
    ? n()
    : s(o.get());
}

template <class T>
struct containable<local_option<T>> {
  static constexpr bool contains(const T& n, const local_option<T>& f) noexcept {
    return match(f,
      []()             { return false; },
      [&n](const T& m) { return n == m; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct container<local_option<T>> {
  static constexpr size_t length(const local_option<T>& o) noexcept {
    return match(o,
      []()           { return 0; },
      [](const T& n) { return 1; }
    );
  }
  static constexpr bool is_empty(const local_option<T>& o) noexcept {
    return match(o,
      []()           { return true; },
      [](const T& n) { return false; }
    ) ;
  }
  static constexpr bool exists = true;
};

template <class T>
struct eq<local_option<T>> {
  static constexpr bool equals(const local_option<T>& lhs,
                               const local_option<T>& rhs) noexcept
  {
    return match(lhs,
      [&](){
        return match(rhs,
          []()           { return true; },
          [](const T& y) { return false; }
        );
      },
      [&](const T& x){
        return match(rhs,
          []()            { return false; },
          [&](const T& y) { return x == y; }
        );
      }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
constexpr inline bool operator==(const local_option<T>& lhs, const local_option<T>& rhs) noexcept {
  return eq<local_option<T>>::equals(lhs, rhs);
}

template <class T>
constexpr inline bool operator!=(const local_option<T>& lhs, const local_option<T>& rhs) noexcept {
  return !eq<local_option<T>>::equals(lhs, rhs);
}

template <class T>
struct hashable<local_option<T>> {
  static constexpr int hash(const local_option<T>& o) noexcept {
    return match(o,
      []()           { return 0; },
      [](const T& n) { return hashable<T>::hash(n); }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct zero_val<local_option<T>> {
  static constexpr local_option<T> zero() { return local_none<T>(); }
  static constexpr bool exists = true;
};

template <class T>
struct semigroup<local_option<T>> {
  static constexpr local_option<T> add(const local_option<T>& lhs,
                                 const local_option<T>& rhs) noexcept
  {
    return match(lhs,
      [&rhs]()        { return rhs; },
      [&](const T& x) {
        return match(rhs,
          [&lhs]()        { return lhs; },
          [&](const T& y) { return local_some<T>(x + y); }
        );
      }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct monoid<local_option<T>> {
  static constexpr bool exists = true;
};

template <class T>
struct filterable<local_option<T>> {
  template <class P>
  static constexpr local_option<T> filter(P p, const local_option<T>& n) noexcept {
    return match(n,
                 []()            { return local_none<T>(); },
                 [&](const T& m) { return p(m) ? n : local_none<T>(); }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct ord<local_option<T>> {

  static constexpr Ordering cmp(const local_option<T>& lhs,
                                const local_option<T>& rhs) noexcept
  {
    return match(lhs,
      [&rhs]() {
        return match(rhs,
          []()           { return EQUAL; },
          [](const T& x) { return LESS; }
        );
      },
      [&rhs](const T& x) {
        return match(rhs,
          []()             { return GREATER; },
          [&x](const T& y) { return traitorous::cmp(x, y); }
        );
      }
    );
  }

  static constexpr const local_option<T>& min(const local_option<T>& lhs,
                                        const local_option<T>& rhs) noexcept
  {
    return (ord<local_option<T>>::cmp(lhs, rhs) == GREATER) ? rhs : lhs;
  }
  static constexpr const local_option<T>& max(const local_option<T>& lhs,
                                        const local_option<T>& rhs) noexcept
  {
    return (ord<local_option<T>>::cmp(lhs, rhs) == LESS) ? rhs : lhs;
  }
  static constexpr bool exists = true;
};

template <class T>
struct functor<local_option<T>> {
  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr local_option<B> map(F f, const local_option<T>& n) noexcept {
    return match(n,
      []()             { return local_none<B>(); },
      [&f](const T& m) { return local_some<B>(f(m)); }
    );
  }
  static constexpr bool exists = true;
};

template <class F>
struct applicative<local_option<F>> {
  template <class A, class B = typename std::result_of<F(A)>::type>
  static constexpr local_option<B> ap(const local_option<F>& f, const local_option<A>& a) noexcept {
    return f >>= [&a](const F& fn) { return map(fn, a); };
  }
  static constexpr bool exists = true;
};

template <class T>
struct alternative<local_option<T>> {
  static constexpr local_option<T> alt(const local_option<T>& lhs,
                                 const local_option<T>& rhs) noexcept
  {
    return match(lhs,
      [&rhs]()           { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
constexpr inline local_option<T> operator||(const local_option<T>& lhs, const local_option<T>& rhs) noexcept {
  return alternative<local_option<T>>::alt(lhs, rhs);
}

template <class T>
struct monad<local_option<T>> {
  template <class F,
            class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr local_option<B> flat_map(F f, const local_option<T>& m) noexcept {
    return match(m,
      [&m]()           { return local_none<B>(); },
      [&f](const T& t) { return f(t); }
    );
  }
  template <class B>
  static constexpr local_option<B> then(const local_option<T>& m,
                                  const local_option<B>& n) noexcept
  {
    return match(m,
      []()        { return local_none<B>(); },
      [&](auto _) { return n; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct monad_plus<local_option<T>> {
  static constexpr local_option<T> mplus(const local_option<T>& lhs,
                                   const local_option<T>& rhs) noexcept
  {
    return match(lhs,
      [&rhs]()           { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct foldable<local_option<T>> {
  static constexpr T fold(const local_option<T>& n) noexcept {
    return match(n,
      []()             { return zero_val<T>::zero(); },
      [&n](const T& m) { return m; }
    );
  }
  template <class Fn,
            class M = typename std::result_of<Fn(T)>::type>
  static constexpr M fold_map(Fn f, const local_option<T>& n) noexcept {
    return match(n,
      []()             { return zero_val<M>::zero(); },
      [&f](const T& m) { return f(m); }
    );
  }
  template <class Fn, class B>
  static constexpr B foldr(Fn f,
                           const B& init,
                           const local_option<T>& n) noexcept
  {
    return match(n,
      [&]()           { return init; },
      [&](const T& m) { return f(init, m); }
    );
  }
  template <class Fn, class B>
  static constexpr B foldl(Fn f,
                           const B& init,
                           const local_option<T>& n) noexcept
  {
    return match(n,
      [&]()           { return init; },
      [&](const T& m) { return f(init, m); }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct unwrappable<local_option<T>> {
  template <class D>
  static constexpr T get_or_else(D d, const local_option<T>& f) noexcept {
    return match(f,
      [&d]()         { return d(); },
      [](const T& m) { return m; }
    );
  }
  static constexpr T get_or_default(const T& d, const local_option<T>& n) noexcept {
    return match(n,
      [&d]()         { return d; },
      [](const T& m) { return m; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct shows<local_option<T>> {
  static const std::string show(const local_option<T>& n) noexcept {
    return match(n,
      []()           { return std::string("local_none"); },
      [](const T& n) { return std::string("local_some(") + shows<T>::show(n) + ")"; }
    );
  }
  static constexpr bool exists = true;
};

}

#endif