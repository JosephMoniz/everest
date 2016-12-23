#pragma once

#include <everest/strings/string.h>

namespace everest {

enum class CheckedType {
  OK,
  ERROR,
  UNINITIALIZED
};

template<>
class Shows<CheckedType> final {
public:

  static constexpr bool exists = true;

  static String Show(CheckedType n) noexcept {
    switch (n) {
      case CheckedType::OK:            return String("OK");
      case CheckedType::ERROR:         return String("ERROR");
      case CheckedType::UNINITIALIZED: return String("UNINITIALIZED");
    }
  }

};

}