#pragma once

#include <everest/types/string.h>
#include <everest/containers/checked.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template <class E, class T>
using SharedChecked = Shared<Checked<E, T>>;

template <class E, class T>
class Shows<SharedChecked<E, T>> {
public:

  static constexpr bool exists = true;

  static const String Show(const SharedChecked<E, T>& n) noexcept {
    return Match(n,
      [](const E& error) { return String("SharedError(") + Shows<E>::Show(error) + String(")"); },
      [](const T& ok)    { return String("SharedOk(") + Shows<T>::Show(ok) + String(")"); }
    );
  }

};

}