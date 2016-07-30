#pragma once

#include <everest/types/bool.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

class Bool;

template<>
class Eq<Bool> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Bool lhs, const Bool rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}