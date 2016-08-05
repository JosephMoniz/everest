#pragma once

#include <everest/types/mutable/mutable_string.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class MutableString;

template<>
class Copyable<MutableString> final {
public:

  static constexpr bool exists = true;

  static MutableString Copy(const MutableString& string) noexcept {
    return string.Copy();
  }

  static MutableString Copy(MutableString&& string) noexcept {
    return MutableString(std::move(string));
  }

};

}