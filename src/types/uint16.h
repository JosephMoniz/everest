#ifndef TRAITOROUS_TYPES_UINT16
#define TRAITOROUS_TYPES_UINT16 1

#include <cstdint>

#include "traits/eq.h"
#include "traits/ord.h"
#include "traits/bounded.h"
#include "traits/one.h"
#include "traits/monoid.h"
#include "traits/subtract.h"
#include "traits/multiply.h"
#include "traits/divide.h"
#include "traits/remainder.h"
#include "traits/bit_and.h"
#include "traits/bit_or.h"
#include "traits/bit_xor.h"
#include "traits/shift_left.h"
#include "traits/shift_right.h"
#include "traits/show.h"

template <>
struct zero_val<uint16_t> : public default_zero_val<uint16_t> {};

template <>
struct semigroup<uint16_t> : public default_semigroup<uint16_t> {};

template <>
struct monoid<uint16_t> : public default_monoid<uint16_t> {};

template <>
struct subtractable<uint16_t> : public default_subtract<uint16_t> {};

template <>
struct multipliable<uint16_t> : public default_multipliable<uint16_t> {};

template <>
struct dividable<uint16_t> : public default_dividable<uint16_t> {};

template <>
struct bounded<uint16_t> : public default_bounded<uint16_t> {};

template <>
struct eq<uint16_t> : public default_eq<uint16_t> {};

template <>
struct ord<uint16_t> : public default_ord<uint16_t> {};

template <>
struct bit_and<uint16_t> : public default_and<uint16_t> {};

template <>
struct bit_or<uint16_t> : public default_or<uint16_t> {};

template <>
struct bit_xor<uint16_t> : public default_xor<uint16_t> {};

template <>
struct one_val<uint16_t> {
  static constexpr uint16_t one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<uint16_t> {
  static const std::string show(uint16_t n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

#endif
