#ifndef TRAITOROUS_TYPES_INT8
#define TRAITOROUS_TYPES_INT8 1

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
struct zero_val<int8_t> : public default_zero_val<int8_t> {};

template <>
struct semigroup<int8_t> : public default_semigroup<int8_t> {};

template <>
struct monoid<int8_t> : public default_monoid<int8_t> {};

template <>
struct subtractable<int8_t> : public default_subtract<int8_t> {};

template <>
struct multipliable<int8_t> : public default_multipliable<int8_t> {};

template <>
struct dividable<int8_t> : public default_dividable<int8_t> {};

template <>
struct bounded<int8_t> : public default_bounded<int8_t> {};

template <>
struct eq<int8_t> : public default_eq<int8_t> {};

template <>
struct ord<int8_t> : public default_ord<int8_t> {};

template <>
struct bit_and<int8_t> : public default_and<int8_t> {};

template <>
struct bit_or<int8_t> : public default_or<int8_t> {};

template <>
struct bit_xor<int8_t> : public default_xor<int8_t> {};

template <>
struct one_val<int8_t> {
  static constexpr int8_t one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<int8_t> {
  static const std::string show(int8_t n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

#endif
