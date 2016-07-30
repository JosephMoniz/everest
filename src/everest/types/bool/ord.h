#pragma once

#include <everest/types/bool.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class Bool;

template<>
class Ord<Bool> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const Bool lhs, const Bool rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static const Bool Min(const Bool lhs, const Bool rhs) noexcept {
    return lhs.Min(rhs);
  }

  static const Bool Max(const Bool lhs, const Bool rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}