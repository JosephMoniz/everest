#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Hashable<Checked<E, T>> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const Checked<E, T>& checked) noexcept {
    return checked.Hash();
  }

};

}