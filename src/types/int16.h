#ifndef TRAITOROUS_TYPES_INT16
#define TRAITOROUS_TYPES_INT16 1

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
struct zero_val<int16_t> : public default_zero_val<int16_t> {};

template <>
struct semigroup<int16_t> : public default_semigroup<int16_t> {};

template <>
struct monoid<int16_t> : public default_monoid<int16_t> {};

template <>
struct subtractable<int16_t> : public default_subtract<int16_t> {};

template <>
struct multipliable<int16_t> : public default_multipliable<int16_t> {};

template <>
struct dividable<int16_t> : public default_dividable<int16_t> {};

template <>
struct modulus<int16_t> : public default_modulus<int16_t> {};

template <>
struct bounded<int16_t> : public default_bounded<int16_t> {};

template <>
struct eq<int16_t> : public default_eq<int16_t> {};

template <>
struct ord<int16_t> : public default_ord<int16_t> {};

template <>
struct bit_and<int16_t> : public default_and<int16_t> {};

template <>
struct bit_or<int16_t> : public default_or<int16_t> {};

template <>
struct bit_xor<int16_t> : public default_xor<int16_t> {};

template <>
struct one_val<int16_t> {
  static constexpr int16_t one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<int16_t> {
  static const std::string show(int16_t n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

#endif
