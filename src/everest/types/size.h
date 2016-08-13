#pragma once

#include <cstddef>
#include <cmath>
#include <limits>
#include <everest/traits/unlawful/ord.h>
#include <everest/types/expressive/hash_value.h>
#include <everest/strings/string.h>

namespace everest {

class Size final {

  size_t _value;

public:

  Size(size_t value) noexcept : _value(value) { }

  size_t Value() const noexcept {
    return _value;
  }

  explicit operator bool() const {
    return _value != 0;
  }

  operator size_t() const {
    return _value;
  }

  Size Add(const Size other) const noexcept {
    return Size(_value + other.Value());
  }

  Size Subtract(const Size other) const noexcept {
    return Size(_value - other.Value());
  }

  Size Multiply(const Size other) const noexcept {
    return Size(_value * other.Value());
  }

  Size Divide(const Size other) const noexcept {
    return Size(_value / other.Value());
  }

  Size Modulo(const Size other) const noexcept {
    return Size(_value % other.Value());
  }

  bool Equals(const Size other) const noexcept {
    return _value == other.Value();
  }

  Ordering Compare(const Size other) const noexcept {
    return (_value < other.Value())
      ? Ordering::LESS
      : (_value > other.Value())
        ? Ordering::GREATER
        : Ordering::EQUAL;
  }

  Size Min(const Size other) const noexcept {
    return (Compare(other) == Ordering::GREATER)
      ? other
      : *this;
  }

  Size Max(const Size other) const noexcept {
    return (Compare(other) == Ordering::LESS)
      ? other
      : *this;
  }

  double Sqrt(const Size number) const noexcept {
    return std::sqrt(number.Value());
  }

  Size BinaryAnd(const Size other) const noexcept {
    return Size(_value & other.Value());
  }

  Size BinaryOr(const Size other) const noexcept {
    return Size(_value | other.Value());
  }

  Size BinaryXor(const Size other) const noexcept {
    return Size(_value ^ other.Value());
  }

  HashValue Hash() const noexcept {
    return HashValue((unsigned int) _value);
  }

  Size Copy() const noexcept {
    return Size(_value);
  }

  String Show() const noexcept {

  }

  static Size MinValue() noexcept {
    return Size(std::numeric_limits<size_t>::min());
  }

  static Size MaxValue() noexcept {
    return Size(std::numeric_limits<size_t>::max());
  }

  static Size Zero() noexcept {
    return Size(0);
  }

  static Size One() noexcept {
    return Size(1);
  }

};

}
