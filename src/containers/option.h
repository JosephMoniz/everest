#ifndef TRAITOROUS_CONTAINERS_OPTION
#define TRAITOROUS_CONTAINERS_OPTION 1

#include <string>

#include "core/tagged_union.h"

#include "traits/monad_plus.h"

#include "traits/alternative.h"
#include "traits/applicative.h"
#include "traits/catamorphism.h"
#include "traits/container.h"
#include "traits/eq.h"
#include "traits/foldable.h"
#include "traits/functor.h"
#include "traits/hashable.h"
#include "traits/monad.h"
#include "traits/monoid.h"
#include "traits/ord.h"
#include "traits/semigroup.h"
#include "traits/show.h"
#include "traits/zero.h"

namespace traitorous {

struct none {} none_instance;

struct some_ {} some;

template <class T>
class option : public tagged_union<T, none> {
public:

  option(const T& val): tagged_union<T, none>(val) {}

  option(size_t id, void* val): tagged_union<T, none>(id, val) {}

  option(const option<T>& val): tagged_union<T, none>(val) {}

  option(const option<T>&& val): tagged_union<T, none>(val) {}

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

};

template <class T>
option<T> make_none() {
  return option<T>(typeid(none).hash_code(), &none_instance);
}

template <class T>
struct catamorphism<option<T>> {
  template <class R>
  static constexpr R cata(const option<T>& o,
                          std::function<R()> n,
                          std::function<R(const T&)> s) noexcept
  {
    return (o.template is<none>()) ? n() : s(o.template get<T>());
  }
  static constexpr bool exists = true;
};

template <class T>
struct container<option<T>> {
  static constexpr size_t length(const option<T>& o) noexcept {
    return catamorphism<option<T>>::cata<size_t>(o,
      [](){ return 0; },
      [](const T& n){ return 1; }
    );
  }
  static constexpr bool is_empty(const option<T>& o) noexcept {
    return catamorphism<option<T>>::cata<bool>(o,
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
    return catamorphism<option<T>>::cata<bool>(lhs,
      [&](){
        return catamorphism<option<T>>::cata<bool>(rhs,
          [](){ return true; },
          [](const T& y){ return false; }
        );
      },
      [&](const T& x){
        return catamorphism<option<T>>::cata<bool>(rhs,
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
    return catamorphism<option<T>>::cata<int>(o,
      [](){ return 0; },
      [](const T& n) { return hashable<T>::hash(n); }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct zero_val<option<T>> {
  static constexpr option<T> zero() { return make_none<T>(); }
  static constexpr bool exists = true;
};

template <class T>
struct semigroup<option<T>> {
  static constexpr option<T> add(const option<T>& lhs,
                                 const option<T>& rhs) noexcept
  {
    return catamorphism<option<T>>::cata<option<T>>(lhs,
      [&rhs]() { return rhs; },
      [&](const T& x) {
        return catamorphism<option<T>>::cata<option<T>>(rhs,
          [&lhs]() { return lhs; },
          [&](const T& y){ return option<T>(semigroup<T>::add(x, y)); }
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
    return catamorphism<option<T>>::cata<Ordering>(lhs,
      [&rhs]() {
        return catamorphism<option<T>>::cata<Ordering>(rhs,
          []() { return EQUAL; },
          [](const T& x) { return LESS; }
        );
      },
      [&rhs](const T& x) {
        return catamorphism<option<T>>::cata<Ordering>(rhs,
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
  template <class R>
  static constexpr option<R> map(std::function<R(const T&)> f,
                                 const option<T>& n) noexcept
  {
    return catamorphism<option<T>>::cata<option<R>>(n,
      []() { return make_none<R>(); },
      [f](const T& n) { return option<R>(f(n)); }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct applicative<option<T>> {
  template <class B>
  static constexpr option<B> ap(option<std::function<B(const T&)>> f,
                                const option<T>& a) noexcept
  {
    return catamorphism<option<T>>::cata<option<B>>(f,
      []() { return make_none<B>(); },
      [&a](std::function<B(const T&)> fn) {
        return functor<option<T>>::map(fn, a);
      }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct alternative<option<T>> {
  static constexpr option<T>& alt(const option<T>& lhs,
                                  const option<T>& rhs) noexcept
  {
    return catamorphism<option<T>>::cata<const option<T>&>(lhs,
      [&rhs]() { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct foldable<option<T>> {
  static constexpr T fold(const option<T>& n) noexcept {
    return catamorphism<option<T>>::cata<T>(n,
      []() { return zero_val<T>::zero(); },
      [&n](const T& m) { return m; }
    );
  }
  template <class M>
  static constexpr M foldMap(std::function<M(const T&)> f,
                             const option<T>& n) noexcept
  {
    return catamorphism<option<T>>::cata<M>(n,
      []() { return zero_val<T>::zero(); },
      [&f](const T& m) { return f(m); }
    );
  }
  template <class B>
  static constexpr B foldr(std::function<B(const B&, const T&)> f,
                           const B& init,
                           const option<T>& n) noexcept
  {
    return catamorphism<option<T>>::cata<B>(n,
      [&init]() { return init; },
      [&f](const T& m) { return m; }
    );
  }
  template <class B>
  static constexpr B foldl(std::function<B(const B&, const T&)> f,
                           const B& init,
                           const option<T>& n) noexcept
  {
    return catamorphism<option<T>>::cata<B>(n,
      [&init]() { return init; },
      [&f](const T& m) { return m; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct monad<option<T>> {
  template <class B>
  static constexpr option<B> flatMap(const option<T>& m,
                                     std::function<option<B>(const T&)> f) noexcept
  {
    return catamorphism<option<T>>::cata<option<B>>(m,
      [&m]() { return m; },
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
    return catamorphism<option<T>>::cata<const option<T>&>(lhs,
      [&rhs]() { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct shows<option<T>> {
  static const std::string show(const option<T>& n) noexcept {
    return catamorphism<option<T>>::cata<std::string>(n,
      []() { return std::string("None"); },
      [](const T& n) { return std::string("Some(") + shows<T>::show(n) + ")"; }
    );
  }
  static constexpr bool exists = true;
};

}

#endif
