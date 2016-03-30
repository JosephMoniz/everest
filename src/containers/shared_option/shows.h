#pragma once

#include "containers/option.h"
#include "traits/unlawful/show.h"

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class Shows<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  static const String Show(const SharedOption<T>& n) noexcept {
    return Match(n,
      []()           { return String("SharedNone"); },
      [](const T& m) { return String("SharedSome(") + Shows<T>::Show(m) + String(")"); }
    );
  }

};

}
