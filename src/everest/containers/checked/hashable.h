#pragma once

#include <everest/containers/checked.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Hashable<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static constexpr int Hash(const Checked<E, T>& o) noexcept {
    return Match(o,
      [](const E& error) { return Hashable<E>::Hash(error); },
      [](const T& ok)    { return Hashable<T>::Hash(ok); }
    );
  }

};

}