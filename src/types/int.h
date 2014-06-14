#ifndef TRAITOROUS_TYPES_INT
#define TRAITOROUS_TYPES_INT 1

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
struct zero_val<int> : public default_zero_val<int> {};

template <>
struct semigroup<int> : public default_semigroup<int> {};

template <>
struct monoid<int> : public default_monoid<int> {};

template <>
struct subtractable<int> : public default_subtract<int> {};

template <>
struct multipliable<int> : public default_multipliable<int> {};

template <>
struct dividable<int> : public default_dividable<int> {};

template <>
struct modulus<int> : public default_modulus<int> {};

template <>
struct negation<int> : public default_negation<int> {};

template <>
struct bounded<int> : public default_bounded<int> {};

template <>
struct eq<int> : public default_eq<int> {};

template <>
struct ord<int> : public default_ord<int> {};

template <>
struct bit_and<int> : public default_and<int> {};

template <>
struct bit_or<int> : public default_or<int> {};

template <>
struct bit_xor<int> : public default_xor<int> {};

template <>
struct one_val<int> {
  static constexpr int one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<int> {
  static const std::string show(int n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

}

#endif
