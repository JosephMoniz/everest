#pragma once

#include <everest/strings/string.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

class String;

template<>
class Eq<String> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const String& lhs, const String& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}