#pragma once

#include <everest/types/string.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/types/mutable/string/semigroup.h>

namespace everest {

class String;

template<>
class Semigroup<String> final {
public:

  static constexpr bool exists = true;

  static String Add(const String& lhs, const String& rhs) noexcept {
    return String(Semigroup<MutableString>::Add(lhs._wrapped, rhs._wrapped));
  }

  static String Add(String&& lhs, const String& rhs) noexcept {
    return String(Semigroup<MutableString>::Add(std::move(lhs._wrapped), rhs._wrapped));
  }

};

}