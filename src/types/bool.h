#ifndef TRAITOROUS_TYPES_BOOL
#define TRAITOROUS_TYPES_BOOL 1

#include "traits/eq.h"
#include "traits/zero.h"
#include "traits/ord.h"
#include "traits/show.h"

namespace traitorous {

template<>
struct eq<bool> : public default_eq<bool> {};

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
