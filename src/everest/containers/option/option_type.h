#pragma once

#include <everest/types/string.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

enum class OptionType {
  SOME,
  NONE
};

template<>
class Shows<OptionType> {
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