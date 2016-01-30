#ifndef TRAITOROUS_TYPES_BOOL
#define TRAITOROUS_TYPES_BOOL 1

#include "traits/unlawful/eq.h"
#include "traits/unlawful/zero.h"
#include "traits/unlawful/ord.h"
#include "traits/unlawful/show.h"

namespace traitorous {

template<>
class Eq<bool> : public DefaultEq<bool> {};

constexpr inline bool Equals(bool lhs, bool rhs) noexcept {
  return Eq<bool>::Equals(lhs, rhs);
}

inline std::function<bool(bool)> Equals(bool lhs) noexcept {
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
class Shows<bool> {
public:

  static constexpr bool exists = true;

  static std::string Show(bool n) noexcept {
    return n ? std::string("true") : std::string("false");
  }

};

}

#endif
