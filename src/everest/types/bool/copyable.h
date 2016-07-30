#pragma once

#include <everest/types/bool.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class Bool;

template<>
class Copyable<Bool> final {
public:

  static constexpr bool exists = true;

  static Bool Copy(const Bool value) noexcept {
    return value.Copy();
  }

};

}