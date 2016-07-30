#pragma once

#include <everest/types/bool.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

class Bool;

template<>
class Hashable<Bool> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const Bool value) noexcept {
    return value.Hash();
  }

};

}