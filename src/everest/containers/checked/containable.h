#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Containable<Checked<E, T>> final {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& item, const Checked<E, T>& checked) noexcept {
    return checked.Contains(item);
  }

};

}