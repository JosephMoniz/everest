#ifndef TRAITOROUS_TYPES_BOOL
#define TRAITOROUS_TYPES_BOOL 1

#include "traits/unlawful/eq.h"
#include "traits/unlawful/zero.h"
#include "traits/unlawful/ord.h"
#include "traits/unlawful/show.h"

namespace traitorous {

template<>
struct eq<bool> : public default_eq<bool> {};

constexpr inline bool equals(bool lhs, bool rhs) noexcept {
  return eq<bool>::equals(lhs, rhs);
}

inline std::function<bool(bool)> equals(bool lhs) noexcept {
  return [&](bool rhs) {
    return eq<bool>::equals(lhs, rhs);
  };
}

template<>
struct zero_val<bool> {
  static constexpr bool zero() noexcept { return false; }
  static constexpr bool exists = true;
};

template<>
struct ord<bool> : public default_ord<bool> {};

template<>
struct shows<bool> {
  static std::string show(bool n) noexcept {
    return n ? std::string("true") : std::string("false");
  }
  static constexpr bool exists = true;
};

}

#endif
