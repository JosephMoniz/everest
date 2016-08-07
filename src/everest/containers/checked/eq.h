#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class E, class T>
class Checked;

template<class E, class T>
class Eq<Checked<E, T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Checked <E, T>& lhs, const Checked <E, T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}