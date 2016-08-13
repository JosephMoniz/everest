#pragma once

#include <everest/strings/string.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class String;

template <>
class Ord<String> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const String& lhs, const String& rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static const String& Min(const String& lhs, const String& rhs) noexcept {
    return lhs.Min(rhs);
  }

  static const String& Max(const String& lhs, const String& rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}