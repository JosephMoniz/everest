#pragma once

#include <everest/types/string.h>

namespace everest {

enum class CheckedType {
  OK,
  ERROR
};

template<>
class Shows<CheckedType> final {
public:

  static constexpr bool exists = true;

  static String Show(CheckedType n) noexcept {
    switch (n) {
      case CheckedType::OK:    return String("OK");
      case CheckedType::ERROR: return String("ERROR");
    }
  }

};

}