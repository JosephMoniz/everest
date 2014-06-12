#ifndef TRAITOROUS_TYPES_INT32
#define TRAITOROUS_TYPES_INT32 1

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
struct zero_val<int32_t> : public default_zero_val<int32_t> {};

template <>
struct semigroup<int32_t> : public default_semigroup<int32_t> {};

template <>
struct monoid<int32_t> : public default_monoid<int32_t> {};

template <>
struct subtractable<int32_t> : public default_subtract<int32_t> {};

template <>
struct multipliable<int32_t> : public default_multipliable<int32_t> {};

template <>
struct dividable<int32_t> : public default_dividable<int32_t> {};

template <>
struct modulus<int32_t> : public default_modulus<int32_t> {};

template <>
struct bounded<int32_t> : public default_bounded<int32_t> {};

template <>
struct eq<int32_t> : public default_eq<int32_t> {};

template <>
struct ord<int32_t> : public default_ord<int32_t> {};

template <>
struct bit_and<int32_t> : public default_and<int32_t> {};

template <>
struct bit_or<int32_t> : public default_or<int32_t> {};

template <>
struct bit_xor<int32_t> : public default_xor<int32_t> {};

template <>
struct one_val<int32_t> {
  static constexpr int32_t one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<int32_t> {
  static const std::string show(int32_t n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

#endif
