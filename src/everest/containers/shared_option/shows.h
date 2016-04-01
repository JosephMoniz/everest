#pragma once

#include <everest/containers/option.h>
#include <everest/containers/shared.h>
#include <everest/types/string.h>

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
