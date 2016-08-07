#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Container<Checked<E, T>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const Checked<E, T>& checked) noexcept {
    return checked.Length();
  }

  static bool IsEmpty(const Checked<E, T>& checked) noexcept {
    return checked.IsEmpty();
  }

};

}