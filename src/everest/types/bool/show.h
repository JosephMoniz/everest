#pragma once

#include <everest/types/bool.h>
#include <everest/traits/unlawful/show.h>
#include <everest/strings/string.h>

namespace everest {

class Bool;

template<>
class Shows<Bool> final {
public:

  static constexpr bool exists = true;

  static String Show(Bool value) noexcept {
    return value.Show();
  }

};

}