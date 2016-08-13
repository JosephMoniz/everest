#pragma once

#include <everest/strings/string.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

class String;

template<>
class Iteration<String> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const String& string, F function) noexcept {
    string.ForEach(function);
  }

};

}