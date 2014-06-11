#ifndef TRAITOROUS_CONTAINERS_MONOIDS_MIN
#define TRAITOROUS_CONTAINERS_MONOIDS_MIN 1

#include <string>

#include "traits/ord.h"
#include "traits/zero.h"
#include "traits/semigroup.h"
#include "traits/monoid.h"
#include "traits/show.h"

template <class T,
          class = typename std::enable_if<ord<T>::exists>::type,
          class = typename std::enable_if<zero_val<T>::exists>::type>
class min_monoid {
private:
  const T _n;
public:
  min_monoid(const T& n): _n(n) {}
  constexpr T value() { return _n; }
};

template <class T>
struct zero_val<min_monoid<T>> {
  static constexpr T zero() { return zero_val<min_monoid<T>>::zero(); }
  static constexpr bool exists = true;
};

template <class T>
struct semigroup<min_monoid<T>> {
  static constexpr min_monoid<T> add(const min_monoid<T>& lhs,
                                     const min_monoid<T>& rhs)
  {
    return ord<T>::min(lhs.value(), rhs.value());
  }
  static constexpr bool exists = true;
};

template <class T>
struct monoid<min_monoid<T>> {
  static constexpr bool exists = true;
};

template <class T>
struct shows<min_monoid<T>> {
  static const std::string show(const min_monoid<T>& n) {
    return std::string("min_monoid(") + shows<T>::show(n.value()) + ")";
  }
  static constexpr bool exists = true;
};

#endif
