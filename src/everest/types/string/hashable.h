#pragma once

#include <everest/types/string.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

class String;

template<>
class Hashable<String> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const String& string) noexcept {
    return string.Hash();
  }

};

}