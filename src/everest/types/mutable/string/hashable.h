#pragma once

#include <everest/types/mutable/mutable_string.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

class MutableString;

template<>
class Hashable<MutableString> {
public:

  static constexpr bool exists = true;

  static int Hash(const MutableString& string) noexcept {
    int result = 37;
    ForEach(string, [&](char item) {
      result = 37 * result + (int) item;
    });
    return result;
  }

};

}