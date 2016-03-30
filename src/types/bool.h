#pragma once

#include "traits/unlawful/eq.h"
#include "traits/unlawful/zero.h"
#include "traits/unlawful/ord.h"
#include "traits/unlawful/show.h"
#include "traits/unlawful/hashable.h"
#include "functions/types.h"

namespace traitorous {

using Bool = bool;

template<>
class Eq<bool> : public DefaultEq<bool> {};

constexpr inline bool Equals(bool lhs, bool rhs) noexcept {
  return Eq<bool>::Equals(lhs, rhs);
}

inline Function<bool, bool> Equals(bool lhs) noexcept {
  return [&](bool rhs) {
    return Eq<bool>::Equals(lhs, rhs);
  };
}

template<>
class ZeroVal<bool> {
public:

  static constexpr bool exists = true;

  static constexpr bool Zero() noexcept {
    return false;
  }

};

template<>
class Ord<bool> : public DefaultOrd<bool> {};

template<>
class Hashable<bool> : public DefaultHashable<bool> {};

template<>
class Shows<bool> {
public:

  static constexpr bool exists = true;

  static String Show(bool n) noexcept {
    return n ? String("true") : String("false");
  }

};

}

