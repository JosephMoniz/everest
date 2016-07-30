#pragma once

#include <cstdint>

namespace everest {

class UInt8 final {

  uint8_t _value;

public:

  UInt8(uint8_t value) noexcept : _value(value) { }

  uint8_t Value() const noexcept {
    return _value;
  }

  explicit operator bool() const {
    return _value != 0;
  }

  operator uint8_t() const {
    return _value;
  }

  UInt8 Add(const UInt8 other) const noexcept {
    return UInt8(_value + other.Value());
  }

  UInt8 Subtract(const UInt8 other) const noexcept {
    return UInt8(_value - other.Value());
  }

  UInt8 Multiply(const UInt8 other) const noexcept {
    return UInt8(_value * other.Value());
  }

  UInt8 Divide(const UInt8 other) const noexcept {
    return UInt8(_value / other.Value());
  }

  UInt8 Modulo(const UInt8 other) const noexcept {
    return UInt8(_value % other.Value());
  }

  bool Equals(const UInt8 other) const noexcept {
    return _value == other.Value();
  }

  Ordering Compare(const UInt8 other) const noexcept {
    return Ord<uint8_t>::Compare(_value, other.Value());
  }

  UInt8 Min(const UInt8 other) const noexcept {
    return UInt8(Ord<uint8_t>::Min(_value, other.Value()));
  }

  UInt8 Max(const UInt8 other) const noexcept {
    return UInt8(Ord<uint8_t>::Max(_value, other.Value()));
  }

  double Sqrt(const UInt8 number) const noexcept {
    return std::sqrt(number.Value());
  }

  UInt8 BinaryAnd(const UInt8 other) const noexcept {
    return UInt8(_value & other.Value());
  }

  UInt8 BinaryOr(const UInt8 other) const noexcept {
    return UInt8(_value | other.Value());
  }

  UInt8 BinaryXor(const UInt8 other) const noexcept {
    return UInt8(_value ^ other.Value());
  }

  HashValue Hash() const noexcept {
    return HashValue((unsigned int) _value);
  }

  UInt8 Copy() const noexcept {
    return UInt8(_value);
  }

  String Show() const noexcept {
    return Shows<uint8_t>::Show(_value);
  }

  String ToHex() const noexcept {
    return Hexable<uint8_t>::ToHex(_value);
  }

  static UInt8 MinValue() noexcept {
    return UInt8(std::numeric_limits<uint8_t>::min());
  }

  static UInt8 MaxValue() noexcept {
    return UInt8(std::numeric_limits<uint8_t>::max());
  }

  static UInt8 Zero() noexcept {
    return UInt8(0);
  }

  static UInt8 One() noexcept {
    return UInt8(1);
  }

};

}

