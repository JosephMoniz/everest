#ifndef TRAITOROUS_CONTAINERS_OPTION_ORD
#define TRAITOROUS_CONTAINERS_OPTION_ORD

#include "containers/option.h"
#include "traits/unlawful/ord.h"

namespace traitorous {

template<class T>
class Ord<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const Option<T> &lhs, const Option<T> &rhs) noexcept {
    return Match(lhs,
      [&rhs]() {
        return Match(rhs,
          []()           { return EQUAL; },
          [](const T &x) { return LESS; }
        );
      },
      [&rhs](const T &x) {
        return Match(rhs,
          []()             { return GREATER; },
          [&x](const T &y) { return traitorous::Compare(x, y); }
        );
      }
    );
  }

  static constexpr const Option<T>& Min(const Option<T> &lhs, const Option<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const Option<T>& Max(const Option<T> &lhs, const Option<T> &rhs) noexcept {
    return (Compare(lhs, rhs) == LESS)
      ? rhs
      : lhs;
  }

};

}

#endif
