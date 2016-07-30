#pragma once

#include <everest/types/bool.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

class Bool;

template<>
class ZeroVal<Bool> final {
public:

  static constexpr bool exists = true;

  static Bool Zero() noexcept {
    return Bool::Zero();
  }

};

}