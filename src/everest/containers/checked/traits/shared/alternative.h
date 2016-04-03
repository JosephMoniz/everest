#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/alternative.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template <class E, class T>
class Alternative<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr SharedChecked<E, T> Alt(const SharedChecked<E, T>& lhs,
                                           const SharedChecked<E, T>& rhs) noexcept
  {
    return Match(lhs,
      [&](const E& error) { return rhs; },
      [&](const T& ok)    { return lhs; }
    );
  }

};

}