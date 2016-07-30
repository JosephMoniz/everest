#pragma once

#include <cstdint>

namespace everest {

class UInt32 final {

  uint32_t _value;

public:

  UInt32(uint32_t value) noexcept : _value(value) { }

  uint32_t Value() const noexcept {
    return _value;
  }

  explicit operator bool() const {
    return _value != 0;
  }

  operator uint32_t() const {
    return _value;
  }

  UInt32 Add(const UInt32 other) const noexcept {
    return UInt32(_value + other.Value());
  }

  UInt32 Subtract(const UInt32 other) const noexcept {
    return UInt32(_value - other.Value());
  }

  UInt32 Multiply(const UInt32 other) const noexcept {
    return UInt32(_value * other.Value());
  }

  UInt32 Divide(const UInt32 other) const noexcept {
    return UInt32(_value / other.Value());
  }

  UInt32 Modulo(const UInt32 other) const noexcept {
    return UInt32(_value % other.Value());
  }

  bool Equals(const UInt32 other) const noexcept {
    return _value == other.Value();
  }

  Ordering Compare(const UInt32 other) const noexcept {
    return Ord<uint32_t>::Compare(_value, other.Value());
  }

  UInt32 Min(const UInt32 other) const noexcept {
    return UInt32(Ord<uint32_t>::Min(_value, other.Value()));
  }

  UInt32 Max(const UInt32 other) const noexcept {
    return UInt32(Ord<uint32_t>::Max(_value, other.Value()));
  }

  double Sqrt(const UInt32 number) const noexcept {
    return std::sqrt(number.Value());
  }

  UInt32 BinaryAnd(const UInt32 other) const noexcept {
    return UInt32(_value & other.Value());
  }

  UInt32 BinaryOr(const UInt32 other) const noexcept {
    return UInt32(_value | other.Value());
  }

  UInt32 BinaryXor(const UInt32 other) const noexcept {
    return UInt32(_value ^ other.Value());
  }

  HashValue Hash() const noexcept {
    return HashValue((unsigned int) _value);
  }

  UInt32 Copy() const noexcept {
    return UInt32(_value);
  }

  String Show() const noexcept {
    return Shows<uint32_t>::Show(_value);
  }

  String ToHex() const noexcept {
    return Hexable<uint32_t>::ToHex(_value);
  }

  static UInt32 MinValue() noexcept {
    return UInt32(std::numeric_limits<uint32_t>::min());
  }

  static UInt32 MaxValue() noexcept {
    return UInt32(std::numeric_limits<uint32_t>::max());
  }

  static UInt32 Zero() noexcept {
    return UInt32(0);
  }

  static UInt32 One() noexcept {
    return UInt32(1);
  }

};

}

