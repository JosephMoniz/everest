#ifndef TRAITOROUS_CONTAINERS_MONOIDS_MAX
#define TRAITOROUS_CONTAINERS_MONOIDS_MAX 1

#include <string>

#include "traits/bounded.h"
#include "traits/eq.h"
#include "traits/monoid.h"
#include "traits/ord.h"
#include "traits/semigroup.h"
#include "traits/show.h"
#include "traits/zero.h"

namespace traitorous {

template <class T,
          class = typename std::enable_if<ord<T>::exists>::type,
          class = typename std::enable_if<bounded<T>::exists>::type>
class max_monoid {
private:
  const T _n;
public:

  constexpr max_monoid(const T& n): _n(n) {}

  constexpr inline T value() noexcept { return _n; }

  constexpr inline max_monoid<T> add(const max_monoid<T>& lhs,
                                     const max_monoid<T>& rhs) noexcept
  {
    return traitorous::add(lhs, rhs);
  }

  constexpr inline bool equals(const max_monoid<T>& lhs,
                               const max_monoid<T>& rhs) noexcept
  {
    return traitorous::equals(lhs, rhs);
  }

};

template <class T>
struct zero_val<max_monoid<T>> {
  static constexpr max_monoid<T> zero() noexcept {
    return max_monoid<T>(bounded<T>::min_value());
  }
  static constexpr bool exists = true;
};

template <class T>
struct semigroup<max_monoid<T>> {
  static constexpr max_monoid<T> add(const max_monoid<T>& lhs,
                                     const max_monoid<T>& rhs) noexcept
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
struct eq<max_monoid<T>> {
  static constexpr bool equals(const max_monoid<T>& lhs,
                               const max_monoid<T>& rhs) noexcept
  {
    return eq<T>::equals(lhs.value(), rhs.value());
  }
  static constexpr bool exists = true;
};

template <class T>
struct shows<max_monoid<T>> {
  static const std::string show(const max_monoid<T>& n) noexcept {
    return std::string("max_monoid(") + shows<T>::show(n.value()) + ")";
  }
  static constexpr bool exists = true;
};

}

#endif
