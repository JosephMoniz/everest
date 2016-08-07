#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/unwrappable.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Unwrappable<Checked<E, T>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static T GetOrElse(F alternative, const Checked<E, T>& checked) noexcept {
    return checked.GetOrElse(alternative);
  }

  static const T& GetOrDefault(const T& alternative, const Checked<E, T>& checked) noexcept {
    return checked.GetOrDefault(alternative);
  }

};

}