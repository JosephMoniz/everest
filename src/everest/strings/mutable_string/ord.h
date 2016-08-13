#pragma once

#include <everest/strings/mutable_string.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class MutableString;

template <>
class Ord<MutableString> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const MutableString& lhs, const MutableString& rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static const MutableString& Min(const MutableString& lhs, const MutableString& rhs) noexcept {
    return lhs.Min(rhs);
  }

  static const MutableString& Max(const MutableString& lhs, const MutableString& rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}