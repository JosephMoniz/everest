#ifndef TRAITOROUS_TYPES_UINT
#define TRAITOROUS_TYPES_UINT 1

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

template <>
struct zero_val<unsigned int> : public default_zero_val<unsigned int> {};

template <>
struct semigroup<unsigned int> : public default_semigroup<unsigned int> {};

template <>
struct monoid<unsigned int> : public default_monoid<unsigned int> {};

template <>
struct subtractable<unsigned int> : public default_subtract<unsigned int> {};

template <>
struct multipliable<unsigned int> : public default_multipliable<unsigned int> {};

template <>
struct dividable<unsigned int> : public default_dividable<unsigned int> {};

template <>
struct modulus<unsigned int> : public default_modulus<unsigned int> {};

template <>
struct negation<unsigned int> : public default_negation<unsigned int> {};

template <>
struct bounded<unsigned int> : public default_bounded<unsigned int> {};

template <>
struct eq<unsigned int> : public default_eq<unsigned int> {};

template <>
struct ord<unsigned int> : public default_ord<unsigned int> {};

template <>
struct bit_and<unsigned int> : public default_and<unsigned int> {};

template <>
struct bit_or<unsigned int> : public default_or<unsigned int> {};

template <>
struct bit_xor<unsigned int> : public default_xor<unsigned int> {};

template <>
struct one_val<unsigned int> {
  static constexpr unsigned int one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<unsigned int> {
  static const std::string show(unsigned int n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

#endif
