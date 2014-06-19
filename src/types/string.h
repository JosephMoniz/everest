#ifndef TRAITOROUS_TYPES_STRING
#define TRAITOROUS_TYPES_STRING 1

#include <string>

#include "traits/container.h"
#include "traits/eq.h"
#include "traits/zero.h"
#include "traits/semigroup.h"
#include "traits/monoid.h"
#include "traits/ord.h"
#include "traits/show.h"

namespace traitorous {

template<>
struct container<std::string> {
  static size_t length(const std::string& n) noexcept {
    return n.length();
  }
  static bool is_empty(const std::string& n) noexcept {
    return n.length() == 0;
  }
  static constexpr bool exists = true;
};

template<>
struct eq<std::string> : public default_eq<std::string> {};

template<>
struct zero_val<std::string> {
  static std::string zero() noexcept { return std::string(""); }
  static constexpr bool exists = true;
};

template<>
struct semigroup<std::string> : public default_semigroup<std::string> {};

template<>
struct monoid<std::string> {
  static constexpr bool exists = true;
};

template<>
struct ord<std::string> : public default_ord<std::string> {};

template<>
struct shows<std::string> {
  static std::string show(const std::string& n) noexcept { return "\"" + n + "\""; }
  static constexpr bool exists = true;
};

}

#endif
