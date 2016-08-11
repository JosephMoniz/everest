#pragma once

#include <everest/types/expressive/hash_value.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class HashValue;

template <>
class Ord<HashValue> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const HashValue lhs, const HashValue rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static HashValue Min(const HashValue lhs, const HashValue rhs) noexcept {
    return lhs.Min(rhs);
  }

  static HashValue Max(const HashValue lhs, const HashValue rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}