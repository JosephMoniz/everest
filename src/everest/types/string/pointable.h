#pragma once

#include <everest/types/string.h>
#include <everest/traits/unlawful/pointable.h>

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