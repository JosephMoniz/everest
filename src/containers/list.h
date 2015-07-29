#ifndef TRAITOROUS_CONTAINERS_LIST_H
#define TRAITOROUS_CONTAINERS_LIST_H

#include <algorithm>
#include <initializer_list>
#include <memory>
#include <numeric>
#include <list>

#include "local_option.h"
#include "containers/shared_ptr.h"

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

/**
 * TODO: http://www.westpoint.edu/eecs/SiteAssets/SitePages/Faculty%20Publication%20Documents/Okasaki/jfp95queue.pdf
 *       use the spec in section 4 to optimize
 */

namespace traitorous {

using std::shared_ptr;
using std::make_shared;

enum list_type {
  LIST_CONS,
  LIST_NIL
};

template<class T>
class list {
public:

  const list_type _tag;

  const T _item;

  const shared_ptr<list<T>> _next;

  list(const T& item, shared_ptr<list<T>> next) : _tag(LIST_CONS),
                                                  _item(item),
                                                  _next(next) { };

  list(const T& item) : _tag(LIST_CONS),
                        _item(item),
                        _next(make_shared<list<T>>()) { }

  list() : _tag(LIST_NIL),
           _item(T()),
           _next(nullptr) {}

};

template<class T>
const shared_ptr<list<T>> cons(const T& item, shared_ptr<list<T>> next) {
  return make_shared<list<T>>(item, next);
}

template<class T>
const shared_ptr<list<T>> cons(const T& item) {
  return make_shared<list<T>>(item);
}

template<class T>
const shared_ptr<list<T>> cons() {
  return make_shared<list<T>>();
}

template<class T>
const shared_ptr<list<T>> make_list(std::initializer_list<T> l) {
  return std::accumulate(
    std::reverse_iterator<const T*>(l.end()),
    std::reverse_iterator<const T*>(l.begin()),
    cons<T>(),
    [](auto m, auto n) { return cons(n, m); }
  );
}

template <class T,
          class P,
          class N,
          class R = typename std::result_of<N()>::type>
static constexpr R match(const list<T>& o, N n, P p) {
  return o._tag == LIST_NIL
    ? n()
    : p(o._item, o._next);
}

template <class T,
          class P,
          class N,
          class R = typename std::result_of<N()>::type>
static constexpr R match(shared_ptr<list<T>> o, N n, P p) {
  return o
    ? match(*o, n, p)
    : n();
}

template <class T>
struct containable<list<T>> {
  static constexpr bool contains(const T& n, const list<T>& f) noexcept {
    return match(f,
      []()                 { return false; },
      [&](auto x, auto xs) { return (x == n) ? true : contains(n, xs); }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct container<list<T>> {
  static constexpr size_t length(const list<T>& o) noexcept {
    return match(o,
      []()                { return 0; },
      [](auto x, auto xs) { return 1 + length(xs); }
    );
  }
  static constexpr bool is_empty(const list<T>& o) noexcept {
    return match(o,
      []()                { return true; },
      [](auto x, auto xs) { return false; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct eq<list<T>> {
  static constexpr bool equals(const list<T>& lhs,
                               const list<T>& rhs) noexcept
  {
    return match(lhs,
      [&]() {
        return match(rhs,
          []()                { return true; },
          [](auto x, auto xs) { return false; }
        );
      },
      [&](auto x, auto xs) {
        return match(rhs,
          []()                 { return false; },
          [&](auto y, auto ys) { return (x == y) ? equals(xs, ys) : false; }
        );
      }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
constexpr inline bool operator==(const list<T>& lhs, const list<T>& rhs) noexcept {
  return equals(lhs, rhs);
}

template <class T>
constexpr inline bool operator!=(const list<T>& lhs, const list<T>& rhs) noexcept {
  return equals(lhs, rhs);
}

template <class T>
constexpr inline bool operator==(const shared_ptr<list<T>>& lhs, const shared_ptr<list<T>>& rhs) noexcept {
  return *lhs == *rhs;
}

template <class T>
constexpr inline bool operator!=(const shared_ptr<list<T>>& lhs, const shared_ptr<list<T>>& rhs) noexcept {
  return !(*lhs == *rhs);
}

template <class T>
struct zero_val<list<T>> {
  static constexpr list<T> zero() { return list<T>(); }
  static constexpr bool exists = true;
};

template <class T>
struct semigroup<shared_ptr<list<T>>> {
  static constexpr shared_ptr<list<T>> add(const shared_ptr<list<T>>& lhs,
                                           const shared_ptr<list<T>>& rhs) noexcept
  {
    return match(lhs,
      [&]()                { return rhs; },
      [&](auto x, auto xs) { return cons<T>(x, add(xs, rhs)); }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct monoid<list<T>> {
  static constexpr bool exists = true;
};

template <class T>
struct monoid<shared_ptr<list<T>>> {
  static constexpr bool exists = true;
};

}

#endif
