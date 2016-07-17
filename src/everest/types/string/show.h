#pragma once

#include <everest/types/string.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

class String;

template <>
class Shows<String> final {
public:

  static constexpr bool exists = true;

  static String Show(const String& string) noexcept {
    return String(Pointer(string));
  }

  static String Show(String&& string) noexcept {
    return std::move(string);
  }

};

}