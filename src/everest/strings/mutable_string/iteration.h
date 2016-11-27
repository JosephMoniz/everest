#pragma once

#include <everest/strings/mutable_string.h>
#include <everest/traits/unlawful/iteration.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class MutableString;

template<>
class Iteration<MutableString> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableString& string, F function) noexcept {
    string.ForEach(function);
  }

};

}