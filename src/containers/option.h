#ifndef TRAITOROUS_CONTAINERS_OPTION
#define TRAITOROUS_CONTAINERS_OPTION 1

#include <string>

#include "core/tagged_union.h"

#include "traits/catamorphism.h"
#include "traits/container.h"
#include "traits/eq.h"
#include "traits/hashable.h"
#include "traits/zero.h"
#include "traits/semigroup.h"
#include "traits/monoid.h"
#include "traits/ord.h"
#include "traits/functor.h"
#include "traits/show.h"

struct none {} none_instance;

struct some_ {} some;

template <class T>
using option = tagged_union<T, none>;

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
  static constexpr option<R> map(const option<T>& n,
                                 std::function<R(const T&)> f) noexcept
  {
    return catamorphism<option<T>>::cata<option<R>>(n,
      []() { return make_none<T>(); },
      [f](const T& n) { return option<R>(f(n)); }
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

#endif
