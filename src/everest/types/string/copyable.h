#pragma once

#include <everest/types/string.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class String;

template<>
class Copyable<String> final {
public:

  static constexpr bool exists = true;

  static String Copy(const String& string) noexcept {
    return string.Copy();
  }

};

}