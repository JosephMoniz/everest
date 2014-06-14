#ifndef TRAITOROUS_TYPES_INT64
#define TRAITOROUS_TYPES_INT64 1

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
#include "traits/negate.h"
#include "traits/bit_and.h"
#include "traits/bit_or.h"
#include "traits/bit_xor.h"
#include "traits/shift_left.h"
#include "traits/shift_right.h"
#include "traits/show.h"

namespace traitorous {

template <>
struct zero_val<int64_t> : public default_zero_val<int64_t> {};

template <>
struct semigroup<int64_t> : public default_semigroup<int64_t> {};

template <>
struct monoid<int64_t> : public default_monoid<int64_t> {};

template <>
struct subtractable<int64_t> : public default_subtract<int64_t> {};

template <>
struct multipliable<int64_t> : public default_multipliable<int64_t> {};

template <>
struct dividable<int64_t> : public default_dividable<int64_t> {};

template <>
struct modulus<int64_t> : public default_modulus<int64_t> {};

template <>
struct negation<int64_t> : public default_negation<int64_t> {};

template <>
struct bounded<int64_t> : public default_bounded<int64_t> {};

template <>
struct eq<int64_t> : public default_eq<int64_t> {};

template <>
struct ord<int64_t> : public default_ord<int64_t> {};

template <>
struct bit_and<int64_t> : public default_and<int64_t> {};

template <>
struct bit_or<int64_t> : public default_or<int64_t> {};

template <>
struct bit_xor<int64_t> : public default_xor<int64_t> {};

template <>
struct one_val<int64_t> {
  static constexpr int64_t one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<int64_t> {
  static const std::string show(int64_t n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

}

#endif
