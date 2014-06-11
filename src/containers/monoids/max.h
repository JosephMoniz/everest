#ifndef TRAITOROUS_CONTAINERS_MONOIDS_MAX
#define TRAITOROUS_CONTAINERS_MONOIDS_MAX 1

#include <string>

#include "traits/ord.h"
#include "traits/zero.h"
#include "traits/semigroup.h"
#include "traits/monoid.h"
#include "traits/show.h"

template <class T,
          class = typename std::enable_if<ord<T>::exists>::type,
          class = typename std::enable_if<zero_val<T>::exists>::type>
class max_monoid {
private:
  const T _n;
public:
  max_monoid(const T& n): _n(n) {}
  constexpr T value() { return _n; }
  constexpr max_monoid<T> add(const max_monoid<T>& lhs, const max_monoid<T>& rhs) {
    return semigroup<max_monoid<T>>::add(lhs, rhs);
  }
};

template <class T>
struct zero_val<max_monoid<T>> {
  static constexpr T zero() { return zero_val<max_monoid<T>>::zero(); }
  static constexpr bool exists = true;
};

template <class T>
struct semigroup<max_monoid<T>> {
  static constexpr max_monoid<T> add(const max_monoid<T>& lhs,
                                     const max_monoid<T>& rhs)
  {
    return ord<T>::max(lhs.value(), rhs.value());
  }
  static constexpr bool exists = true;
};

template <class T>
struct monoid<max_monoid<T>> {
  static constexpr bool exists = true;
};

template <class T>
struct shows<max_monoid<T>> {
  static const std::string show(const max_monoid<T>& n) {
    return std::string("max_monoid(") + shows<T>::show(n.value()) + ")";
  }
  static constexpr bool exists = true;
};

#endif
