#ifndef TRAITOROUS_CONTAINERS_LOCAL_OPTION_ORD
#define TRAITOROUS_CONTAINERS_LOCAL_OPTION_ORD

#include "containers/local_option.h"
#include "traits/unlawful/ord.h"

namespace traitorous {

template<class T>
class ord<local_option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering cmp(const local_option <T> &lhs,
                                const local_option <T> &rhs) noexcept {
    return match(lhs,
      [&rhs]() {
        return match(rhs,
          []()           { return EQUAL; },
          [](const T &x) { return LESS; }
        );
      },
      [&rhs](const T &x) {
        return match(rhs,
          []()             { return GREATER; },
          [&x](const T &y) { return traitorous::cmp(x, y); }
        );
      }
    );
  }

  static constexpr const local_option <T> &min(const local_option <T> &lhs,
                                               const local_option <T> &rhs) noexcept
  {
    return (cmp(lhs, rhs) == GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const local_option <T> &max(const local_option <T> &lhs,
                                               const local_option <T> &rhs) noexcept
  {
    return (cmp(lhs, rhs) == LESS)
      ? rhs
      : lhs;
  }

};

}

#endif
