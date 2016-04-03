#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template <class E, class T>
class Checked;

template<class E, class T>
class Ord<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const Checked<E, T> &lhs,
                                    const Checked<E, T> &rhs) noexcept
  {
    return Match(lhs,
      [&](const E& errorLeft) {
        return Match(rhs,
          [&](const E& errorRight) { return everest::Compare(errorLeft, errorRight); },
          [](const T &ok)          { return Ordering::LESS; }
        );
      },
      [&](const T &okLeft) {
        return Match(rhs,
          [](const E& error)    { return Ordering::GREATER; },
          [&](const T &okRight) { return everest::Compare(okLeft, okRight); }
        );
      }
    );
  }

  static constexpr const Checked<E, T>& Min(const Checked<E, T> &lhs,
                                            const Checked<E, T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const Checked<E, T>& Max(const Checked<E, T> &lhs,
                                            const Checked<E, T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

}