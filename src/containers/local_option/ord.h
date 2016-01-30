#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_ORD
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_ORD

#include "containers/local_option.h"
#include "traits/unlawful/ord.h"

namespace traitorous {

template<class T>
class Ord<LocalOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const LocalOption<T> &lhs,
                                    const LocalOption<T> &rhs) noexcept {
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

  static constexpr const LocalOption<T>& Min(const LocalOption<T> &lhs,
                                             const LocalOption<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const LocalOption<T>& Max(const LocalOption<T> &lhs,
                                             const LocalOption<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == LESS)
      ? rhs
      : lhs;
  }

};

}

#endif
