#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/lawful/alternative.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Alternative<Checked<E, T>> final {
public:

  static constexpr bool exists = true;

  static const Checked<E, T>& Alt(const Checked<E, T>& lhs, const Checked<E, T>& rhs) noexcept {
    return lhs.Alt(rhs);
  }
};

}