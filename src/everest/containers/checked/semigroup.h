#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Semigroup<Checked<E, T>> final {
public:

  static constexpr bool exists = true;

  static Checked<E, T> Add(const Checked<E, T>& lhs, const Checked<E, T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}