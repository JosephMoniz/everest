#pragma once

#include <everest/strings/mutable_string.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class MutableString;

template<>
class pointable<MutableString> final {
public:

  static constexpr bool exists = true;

  static const char* Pointer(const MutableString& string) noexcept {
    return string.Pointer();
  }

};

}