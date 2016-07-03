#pragma once

#include <everest/types/mutable/mutable_string.h>
#include <everest/traits/unlawful/iteration.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class MutableString;

template<>
class Iteration<MutableString> {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableString& string, const F& function) noexcept {
    auto length  = Occupied(string);
    auto pointer = Pointer(string);
    for (size_t i = 0; i < length; i++) {
      function(pointer[i]);
    }
  }

};

}