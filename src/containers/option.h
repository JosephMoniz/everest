#ifndef TRAITOROUS_CONTAINERS_OPTION_H
#define TRAITOROUS_CONTAINERS_OPTION_H

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

using std::shared_ptr;

enum option_type {
  OPTION_SOME,
  OPTION_NONE
};

template<class T>
class option {

  using data_t = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
  const option_type _tag;
  data_t _value;

public:

  option() : _tag(OPTION_NONE) {}

  option(const T& o) : _tag(OPTION_SOME) {
    new (&_value) T(o);
  }

  ~option() noexcept {
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
const option<T> some(const T& o) {
  return option<T>(o);
}

template<class T>
const option<T> none() {
  return option<T>();
}

template <class T,
          class N,
          class S,
          class R = typename std::result_of<N()>::type>
static constexpr R match(const option<T>& o, N n, S s) noexcept {
  return (o.get_type() == OPTION_NONE)
    ? n()
    : s(o.get());
}

template <class T,
          class N,
          class S,
          class R = typename std::result_of<N()>::type>
static constexpr R match(shared_ptr<option<T>> o, N n, S s) noexcept {
  return (o)
    ? match(*o, n, s)
    : n();
}

template <class T>
struct containable<option<T>> {
  static constexpr bool contains(const T& n, const option<T>& f) noexcept {
    return match(f,
      []()             { return false; },
      [&n](const T& m) { return n == m; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct container<option<T>> {
  static constexpr size_t length(const option<T>& o) noexcept {
    return match(o,
      []()           { return 0; },
      [](const T& n) { return 1; }
    );
  }
  static constexpr bool is_empty(const option<T>& o) noexcept {
    return match(o,
      []()           { return true; },
      [](const T& n) { return false; }
    ) ;
  }
  static constexpr bool exists = true;
};

template <class T>
struct eq<option<T>> {
  static constexpr bool equals(const option<T>& lhs,
                               const option<T>& rhs) noexcept
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
constexpr inline bool operator==(const option<T>& lhs, const option<T>& rhs) noexcept {
  return eq<option<T>>::equals(lhs, rhs);
}

template <class T>
constexpr inline bool operator!=(const option<T>& lhs, const option<T>& rhs) noexcept {
  return !eq<option<T>>::equals(lhs, rhs);
}

template <class T>
struct hashable<option<T>> {
  static constexpr int hash(const option<T>& o) noexcept {
    return match(o,
      []()           { return 0; },
      [](const T& n) { return hashable<T>::hash(n); }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct zero_val<option<T>> {
  static constexpr option<T> zero() { return none<T>(); }
  static constexpr bool exists = true;
};

template <class T>
struct semigroup<option<T>> {
  static constexpr option<T> add(const option<T>& lhs,
                                 const option<T>& rhs) noexcept
  {
    return match(lhs,
      [&rhs]()        { return rhs; },
      [&](const T& x) {
        return match(rhs,
          [&lhs]()        { return lhs; },
          [&](const T& y) { return some<T>(x + y); }
        );
      }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct monoid<option<T>> {
  static constexpr bool exists = true;
};

template <class T>
struct filterable<option<T>> {
  template <class P>
  static constexpr option<T> filter(P p, const option<T>& n) noexcept {
    return match(n,
                 []()            { return none<T>(); },
                 [&](const T& m) { return p(m) ? n : none<T>(); }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct ord<option<T>> {

  static constexpr Ordering cmp(const option<T>& lhs,
                                const option<T>& rhs) noexcept
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

  static constexpr const option<T>& min(const option<T>& lhs,
                                        const option<T>& rhs) noexcept
  {
    return (ord<option<T>>::cmp(lhs, rhs) == GREATER) ? rhs : lhs;
  }
  static constexpr const option<T>& max(const option<T>& lhs,
                                        const option<T>& rhs) noexcept
  {
    return (ord<option<T>>::cmp(lhs, rhs) == LESS) ? rhs : lhs;
  }
  static constexpr bool exists = true;
};

template <class T>
struct functor<option<T>> {
  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr option<B> map(F f, const option<T>& n) noexcept {
    return match(n,
      []()             { return none<B>(); },
      [&f](const T& m) { return some<B>(f(m)); }
    );
  }
  static constexpr bool exists = true;
};

template <class F>
struct applicative<option<F>> {
  template <class A, class B = typename std::result_of<F(A)>::type>
  static constexpr option<B> ap(const option<F>& f, const option<A>& a) noexcept {
    return f >>= [&a](const F& fn) { return map(fn, a); };
  }
  static constexpr bool exists = true;
};

template <class T>
struct alternative<option<T>> {
  static constexpr option<T> alt(const option<T>& lhs,
                                 const option<T>& rhs) noexcept
  {
    return match(lhs,
      [&rhs]()           { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
constexpr inline option<T> operator||(const option<T>& lhs, const option<T>& rhs) noexcept {
  return alternative<option<T>>::alt(lhs, rhs);
}

template <class T>
struct monad<option<T>> {
  template <class F,
            class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr option<B> flat_map(F f, const option<T>& m) noexcept {
    return match(m,
      [&m]()           { return none<B>(); },
      [&f](const T& t) { return f(t); }
    );
  }
  template <class B>
  static constexpr option<B> then(const option<T>& m,
                                  const option<B>& n) noexcept
  {
    return match(m,
      []()        { return none<B>(); },
      [&](auto _) { return n; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct monad_plus<option<T>> {
  static constexpr option<T> mplus(const option<T>& lhs,
                                   const option<T>& rhs) noexcept
  {
    return match(lhs,
      [&rhs]()           { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct foldable<option<T>> {
  static constexpr T fold(const option<T>& n) noexcept {
    return match(n,
      []()             { return zero_val<T>::zero(); },
      [&n](const T& m) { return m; }
    );
  }
  template <class Fn,
            class M = typename std::result_of<Fn(T)>::type>
  static constexpr M fold_map(Fn f, const option<T>& n) noexcept {
    return match(n,
      []()             { return zero_val<M>::zero(); },
      [&f](const T& m) { return f(m); }
    );
  }
  template <class Fn, class B>
  static constexpr B foldr(Fn f,
                           const B& init,
                           const option<T>& n) noexcept
  {
    return match(n,
      [&]()           { return init; },
      [&](const T& m) { return f(init, m); }
    );
  }
  template <class Fn, class B>
  static constexpr B foldl(Fn f,
                           const B& init,
                           const option<T>& n) noexcept
  {
    return match(n,
      [&]()           { return init; },
      [&](const T& m) { return f(init, m); }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct unwrappable<option<T>> {
  template <class D>
  static constexpr T get_or_else(D d, const option<T>& f) noexcept {
    return match(f,
      [&d]()         { return d(); },
      [](const T& m) { return m; }
    );
  }
  static constexpr T get_or_default(const T& d, const option<T>& n) noexcept {
    return match(n,
      [&d]()         { return d; },
      [](const T& m) { return m; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct shows<option<T>> {
  static const std::string show(const option<T>& n) noexcept {
    return match(n,
      []()           { return std::string("none"); },
      [](const T& n) { return std::string("some(") + shows<T>::show(n) + ")"; }
    );
  }
  static constexpr bool exists = true;
};

}

#endif