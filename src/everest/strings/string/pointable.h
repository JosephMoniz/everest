#pragma once

#include <everest/strings/string.h>
#include <everest/traits/unlawful/Pointable.h>

namespace everest {

class String;

template<>
class Pointable<String> final {
public:

  static constexpr bool exists = true;

  static const char* Pointer(const String& string) noexcept {
    return string.Pointer();
  }
};

}