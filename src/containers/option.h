#ifndef TRAITOROUS_CONTAINERS_OPTION
#define TRAITOROUS_CONTAINERS_OPTION 1

#include <string>
#include <type_traits>

#include "core/tagged_union.h"

#include "meta/nth_arg.h"
#include "traits/alternative.h"
#include "traits/applicative.h"
#include "traits/container.h"
#include "traits/eq.h"
#include "traits/foldable.h"
#include "traits/functor.h"
#include "traits/hashable.h"
#include "traits/monad.h"
#include "traits/monad_plus.h"
#include "traits/monoid.h"
#include "traits/ord.h"
#include "traits/semigroup.h"
#include "traits/show.h"
#include "traits/zero.h"

namespace traitorous {

struct _none {} none_instance;

template <class T>
class option : public tagged_union<T, _none> {
public:

  option(const T& val): tagged_union<T, _none>(val) {}

  option(size_t id, void* val): tagged_union<T, _none>(id, val) {}

  option(const option<T>& val): tagged_union<T, _none>(val) {}

  option(const option<T>&& val): tagged_union<T, _none>(val) {}

  constexpr size_t length() noexcept {
    return container<option<T>>::length(*this);
  }

  constexpr bool is_empty() noexcept {
    return container<option<T>>::is_empty(*this);
  }

  constexpr bool equals(const option<T> rhs) noexcept {
    return eq<option<T>>::equals(*this, rhs);
  }

  constexpr option<T> add(const option<T>& lhs,
                          const option<T>& rhs) noexcept
  {
    return semigroup<option<T>>::add(lhs, rhs);
  }

  template <class F, class B = typename std::result_of<F(T)>::type>
  constexpr option<B> map(F f) {
    return traitorous::map(f, *this);
  }

  template <class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  constexpr option<B> flat_map(F f) {
    return traitorous::flat_map(f, *this);
  }

  template <class A, class B = typename std::result_of<T(A)>::type>
  constexpr option<B> ap(const option<A>& a) {
    return traitorous::ap(*this, a);
  }

};

template <class T>
option<T> some(const T& t) {
  return option<T>(t);
}

template <class T>
option<T> none() {
  return option<T>(typeid(_none).hash_code(), &none_instance);
}

template <class T,
          class N,
          class S,
          class R = typename std::result_of<N()>::type>
static constexpr R cata(const option<T>& o, N n, S s) noexcept {
  return (o.template is<_none>()) ? n() : s(o.template get<T>());
}

template <class T>
struct container<option<T>> {
  static constexpr size_t length(const option<T>& o) noexcept {
    return cata(o,
      [](){ return 0; },
      [](const T& n){ return 1; }
    );
  }
  static constexpr bool is_empty(const option<T>& o) noexcept {
    return cata(o,
      [](){ return true; },
      [](const T& n){ return false; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct eq<option<T>> {
  static constexpr bool equals(const option<T>& lhs,
                               const option<T>& rhs) noexcept
  {
    return cata(lhs,
      [&](){
        return cata(rhs,
          [](){ return true; },
          [](const T& y){ return false; }
        );
      },
      [&](const T& x){
        return cata(rhs,
          [](){ return false; },
          [&](const T& y){ return eq<T>::equals(x, y); }
        );
      }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct hashable<option<T>> {
  static constexpr int hash(const option<T>& o) noexcept {
    return cata(o,
      [](){ return 0; },
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
    return cata(lhs,
      [&rhs]() { return rhs; },
      [&](const T& x) {
        return cata(rhs,
          [&lhs]() { return lhs; },
          [&](const T& y){ return some(semigroup<T>::add(x, y)); }
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
struct ord<option<T>> {

  static constexpr Ordering cmp(const option<T>& lhs,
                                const option<T>& rhs) noexcept
  {
    return cata(lhs,
      [&rhs]() {
        return cata(rhs,
          []() { return EQUAL; },
          [](const T& x) { return LESS; }
        );
      },
      [&rhs](const T& x) {
        return cata(rhs,
          []() { return GREATER; },
          [&x](const T& y) { return ord<T>::cmp(x, y); }
        );
      }
    );
  }

  static constexpr option<T> min(const option<T>& lhs,
                                 const option<T>& rhs) noexcept
  {
    return (ord<T>::cmp(lhs, rhs) == GREATER) ? rhs : lhs;
  }
  static constexpr option<T> max(const option<T>& lhs,
                                 const option<T>& rhs) noexcept
  {
    return (ord<T>::cmp(lhs, rhs) == LESS) ? rhs : lhs;
  }
  static constexpr bool exists = true;
};

template <class T>
struct functor<option<T>> {
  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr option<B> map(F f, const option<T>& n) noexcept {
    return cata(n,
      []() { return none<B>(); },
      [&f](const T& n) { return some(f(n)); }
    );
  }
  static constexpr bool exists = true;
};

template <class F>
struct applicative<option<F>> {
  template <class A, class B = typename std::result_of<F(A)>::type>
  static constexpr option<B> ap(const option<F>& f, const option<A>& a) noexcept {
    return f >>= [&a](const F& fn) { return a.map(fn); };
  }
  static constexpr bool exists = true;
};

template <class T>
struct alternative<option<T>> {
  static constexpr option<T> alt(const option<T>& lhs,
                                 const option<T>& rhs) noexcept
  {
    return cata(lhs,
      [&rhs]() { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct foldable<option<T>> {
  static constexpr T fold(const option<T>& n) noexcept {
    return cata(n,
      []() { return zero_val<T>::zero(); },
      [&n](const T& m) { return m; }
    );
  }
  template <class M>
  static constexpr M foldMap(std::function<M(const T&)> f,
                             const option<T>& n) noexcept
  {
    return cata(n,
      []() { return zero_val<T>::zero(); },
      [&f](const T& m) { return f(m); }
    );
  }
  template <class B>
  static constexpr B foldr(std::function<B(const B&, const T&)> f,
                           const B& init,
                           const option<T>& n) noexcept
  {
    return cata(n,
      [&init]() { return init; },
      [&f](const T& m) { return m; }
    );
  }
  template <class B>
  static constexpr B foldl(std::function<B(const B&, const T&)> f,
                           const B& init,
                           const option<T>& n) noexcept
  {
    return cata(n,
      [&init]() { return init; },
      [&f](const T& m) { return m; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct monad<option<T>> {
  template <class F,
            class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr option<B> flat_map(F f, const option<T>& m) noexcept {
    return cata(m,
      [&m]() { return none<B>(); },
      [&f](const T& t) { return f(t); }
    );
  }
  template <class B>
  static constexpr option<B>& then(const option<T>& m,
                                   const option<T>& n) noexcept
  {
    return n;
  }
  static constexpr bool exists = true;
};

template <class T>
struct monad_plus<option<T>> {
  static constexpr option<T>& mplus(const option<T>& lhs,
                                  const option<T>& rhs) noexcept
  {
    return cata(lhs,
      [&rhs]() { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct shows<option<T>> {
  static const std::string show(const option<T>& n) noexcept {
    return cata(n,
      []() { return std::string("none"); },
      [](const T& n) { return std::string("some(") + shows<T>::show(n) + ")"; }
    );
  }
  static constexpr bool exists = true;
};

}

#endif
