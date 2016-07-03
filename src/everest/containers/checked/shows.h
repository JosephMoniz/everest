#pragma once

#include <everest/types/string.h>
#include <everest/containers/checked.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template <class E, class T>
class Checked;

template <class E, class T>
class Shows<Checked<E, T>> {
public:

  static constexpr bool exists = true;

  static String Show(const Checked<E, T>& n) noexcept {
    return Match(n,
      [](const E& error) { return String("Error(") + Shows<E>::Show(error) + String(")"); },
      [](const T& ok)    { return String("Ok(") + Shows<T>::Show(ok) + String(")"); }
    );
  }

};

}