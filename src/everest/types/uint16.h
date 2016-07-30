#pragma once

#include <cstdint>

namespace everest {

class UInt16 final {

  uint16_t _value;

public:

  UInt16(uint16_t value) noexcept : _value(value) { }

  uint16_t Value() const noexcept {
    return _value;
  }

  explicit operator bool() const {
    return _value != 0;
  }

  operator uint16_t() const {
    return _value;
  }

  UInt16 Add(const UInt16 other) const noexcept {
    return UInt16(_value + other.Value());
  }

  UInt16 Subtract(const UInt16 other) const noexcept {
    return UInt16(_value - other.Value());
  }

  UInt16 Multiply(const UInt16 other) const noexcept {
    return UInt16(_value * other.Value());
  }

  UInt16 Divide(const UInt16 other) const noexcept {
    return UInt16(_value / other.Value());
  }

  UInt16 Modulo(const UInt16 other) const noexcept {
    return UInt16(_value % other.Value());
  }

  bool Equals(const UInt16 other) const noexcept {
    return _value == other.Value();
  }

  Ordering Compare(const UInt16 other) const noexcept {
    return Ord<uint16_t>::Compare(_value, other.Value());
  }

  UInt16 Min(const UInt16 other) const noexcept {
    return UInt16(Ord<uint16_t>::Min(_value, other.Value()));
  }

  UInt16 Max(const UInt16 other) const noexcept {
    return UInt16(Ord<uint16_t>::Max(_value, other.Value()));
  }

  double Sqrt(const UInt16 number) const noexcept {
    return std::sqrt(number.Value());
  }

  UInt16 BinaryAnd(const UInt16 other) const noexcept {
    return UInt16(_value & other.Value());
  }

  UInt16 BinaryOr(const UInt16 other) const noexcept {
    return UInt16(_value | other.Value());
  }

  UInt16 BinaryXor(const UInt16 other) const noexcept {
    return UInt16(_value ^ other.Value());
  }

  HashValue Hash() const noexcept {
    return HashValue((unsigned int) _value);
  }

  UInt16 Copy() const noexcept {
    return UInt16(_value);
  }

  String Show() const noexcept {
    return Shows<uint16_t>::Show(_value);
  }

  String ToHex() const noexcept {
    return Hexable<uint16_t>::ToHex(_value);
  }

  static UInt16 MinValue() noexcept {
    return UInt16(std::numeric_limits<uint16_t>::min());
  }

  static UInt16 MaxValue() noexcept {
    return UInt16(std::numeric_limits<uint16_t>::max());
  }

  static UInt16 Zero() noexcept {
    return UInt16(0);
  }

  static UInt16 One() noexcept {
    return UInt16(1);
  }

};

}

