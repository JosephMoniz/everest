#pragma once

#include <everest/types/bool.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Bool;

template<>
class Hexable<Bool> final {
public:

  static constexpr bool exists = true;

  static String ToHex(const Bool value) noexcept {
    return value.ToHex();
  }

};

}