#pragma once

#include <everest/strings/string.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

enum class OptionType {
  SOME,
  NONE
};

template<>
class Shows<OptionType> final {
public:

  static constexpr bool exists = true;

  static String Show(OptionType n) noexcept {
    switch (n) {
      case OptionType::SOME: return String("SOME");
      case OptionType::NONE: return String("NONE");
    }
  }

};

}