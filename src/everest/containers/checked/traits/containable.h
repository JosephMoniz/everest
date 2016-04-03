#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Containable<Checked<E, T>, T> {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const T& item, const Checked<E, T>& checked) noexcept {
    return Match(checked,
      [](const E& error)   { return false; },
      [&item](const T& ok) { return item == ok; }
    );
  }

};

}