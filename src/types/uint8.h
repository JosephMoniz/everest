#ifndef TRAITOROUS_TYPES_UINT8
#define TRAITOROUS_TYPES_UINT8 1

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
struct zero_val<uint8_t> : public default_zero_val<uint8_t> {};

template <>
struct semigroup<uint8_t> : public default_semigroup<uint8_t> {};

template <>
struct monoid<uint8_t> : public default_monoid<uint8_t> {};

template <>
struct subtractable<uint8_t> : public default_subtract<uint8_t> {};

template <>
struct multipliable<uint8_t> : public default_multipliable<uint8_t> {};

template <>
struct dividable<uint8_t> : public default_dividable<uint8_t> {};

template <>
struct bounded<uint8_t> : public default_bounded<uint8_t> {};

template <>
struct eq<uint8_t> : public default_eq<uint8_t> {};

template <>
struct ord<uint8_t> : public default_ord<uint8_t> {};

template <>
struct bit_and<uint8_t> : public default_and<uint8_t> {};

template <>
struct bit_or<uint8_t> : public default_or<uint8_t> {};

template <>
struct bit_xor<uint8_t> : public default_xor<uint8_t> {};

template <>
struct one_val<uint8_t> {
  static constexpr uint8_t one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<uint8_t> {
  static const std::string show(uint8_t n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

#endif
