#pragma once

#include <everest/strings/mutable_string.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

class MutableString;

template<>
class Hashable<MutableString> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const MutableString& string) noexcept {
    return string.Hash();
  }

};

}