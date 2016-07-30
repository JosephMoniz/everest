#pragma once

#include <cstdint>

namespace everest {

class Int16 final {

  int16_t _value;

public:

  Int16(int16_t value) noexcept : _value(value) { }

  int16_t Value() const noexcept {
    return _value;
  }

  explicit operator bool() const {
    return _value != 0;
  }

  operator int16_t() const {
    return _value;
  }

  Int16 Add(const Int16 other) const noexcept {
    return Int16(_value + other.Value());
  }

  Int16 Subtract(const Int16 other) const noexcept {
    return Int16(_value - other.Value());
  }

  Int16 Multiply(const Int16 other) const noexcept {
    return Int16(_value * other.Value());
  }

  Int16 Divide(const Int16 other) const noexcept {
    return Int16(_value / other.Value());
  }

  Int16 Modulo(const Int16 other) const noexcept {
    return Int16(_value % other.Value());
  }

  Int16 Negate() const noexcept {
    return Int16(-_value);
  }

  bool Equals(const Int16 other) const noexcept {
    return _value == other.Value();
  }

  Ordering Compare(const Int16 other) const noexcept {
    return Ord<int16_t>::Compare(_value, other.Value());
  }

  Int16 Min(const Int16 other) const noexcept {
    return Int16(Ord<int16_t>::Min(_value, other.Value()));
  }

  Int16 Max(const Int16 other) const noexcept {
    return Int16(Ord<int16_t>::Max(_value, other.Value()));
  }

  double Sqrt() const noexcept {
    return std::sqrt(_value);
  }

  Int16 BinaryAnd(const Int16 other) const noexcept {
    return Int16(_value & other.Value());
  }

  Int16 BinaryOr(const Int16 other) const noexcept {
    return Int16(_value | other.Value());
  }

  Int16 BinaryXor(const Int16 other) const noexcept {
    return Int16(_value ^ other.Value());
  }

  HashValue Hash() const noexcept {
    return HashValue((unsigned int) _value);
  }

  Int16 Copy() const noexcept {
    return Int16(_value);
  }

  String Show() const noexcept {
    return Shows<int16_t>::Show(_value);
  }

  String ToHex() const noexcept {
    return Hexable<int16_t>::ToHex(_value);
  }

  static Int16 MinValue() noexcept {
    return Int16(std::numeric_limits<int16_t>::min());
  }

  static Int16 MaxValue() noexcept {
    return Int16(std::numeric_limits<int16_t>::max());
  }

  static Int16 Zero() noexcept {
    return Int16(0);
  }

  static Int16 One() noexcept {
    return Int16(1);
  }

};

}