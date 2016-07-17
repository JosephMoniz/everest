#pragma once

#include <everest/types/mutable/mutable_string.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class MutableString;

template<>
class Pointable<MutableString> final {
public:

  static constexpr bool exists = true;

  static const char* Pointer(const MutableString& string) noexcept {
    return string.Pointer();
  }

};

}