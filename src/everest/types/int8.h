#pragma once

#include <cstdint>

namespace everest {

class Int8 final {

  int8_t _value;

public:

  Int8(int8_t value) noexcept : _value(value) { }

  int8_t Value() const noexcept {
    return _value;
  }

  explicit operator bool() const {
    return _value != 0;
  }

  operator int8_t() const {
    return _value;
  }

  Int8 Add(const Int8 other) const noexcept {
    return Int8(_value + other.Value());
  }

  Int8 Subtract(const Int8 other) const noexcept {
    return Int8(_value - other.Value());
  }

  Int8 Multiply(const Int8 other) const noexcept {
    return Int8(_value * other.Value());
  }

  Int8 Divide(const Int8 other) const noexcept {
    return Int8(_value / other.Value());
  }

  Int8 Modulo(const Int8 other) const noexcept {
    return Int8(_value % other.Value());
  }

  Int8 Negate() const noexcept {
    return Int8(-_value);
  }

  bool Equals(const Int8 other) const noexcept {
    return _value == other.Value();
  }

  Ordering Compare(const Int8 other) const noexcept {
    return Ord<int8_t>::Compare(_value, other.Value());
  }

  Int8 Min(const Int8 other) const noexcept {
    return Int8(Ord<int8_t>::Min(_value, other.Value()));
  }

  Int8 Max(const Int8 other) const noexcept {
    return Int8(Ord<int8_t>::Max(_value, other.Value()));
  }

  double Sqrt() const noexcept {
    return std::sqrt(_value);
  }

  Int8 BinaryAnd(const Int8 other) const noexcept {
    return Int8(_value & other.Value());
  }

  Int8 BinaryOr(const Int8 other) const noexcept {
    return Int8(_value | other.Value());
  }

  Int8 BinaryXor(const Int8 other) const noexcept {
    return Int8(_value ^ other.Value());
  }

  HashValue Hash() const noexcept {
    return HashValue((unsigned int) _value);
  }

  Int8 Copy() const noexcept {
    return Int8(_value);
  }

  String Show() const noexcept {
    return Shows<int8_t>::Show(_value);
  }

  String ToHex() const noexcept {
    return Hexable<int8_t>::ToHex(_value);
  }

  static Int8 MinValue() noexcept {
    return Int8(std::numeric_limits<int8_t>::min());
  }

  static Int8 MaxValue() noexcept {
    return Int8(std::numeric_limits<int8_t>::max());
  }

  static Int8 Zero() noexcept {
    return Int8(0);
  }

  static Int8 One() noexcept {
    return Int8(1);
  }

};

}

