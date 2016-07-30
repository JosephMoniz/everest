#pragma once

#include <cstdint>

namespace everest {

class Int32 final {

  int32_t _value;

public:

  Int32(int32_t value) noexcept : _value(value) { }

  int32_t Value() const noexcept {
    return _value;
  }

  explicit operator bool() const {
    return _value != 0;
  }

  operator int32_t() const {
    return _value;
  }

  Int32 Add(const Int32 other) const noexcept {
    return Int32(_value + other.Value());
  }

  Int32 Subtract(const Int32 other) const noexcept {
    return Int32(_value - other.Value());
  }

  Int32 Multiply(const Int32 other) const noexcept {
    return Int32(_value * other.Value());
  }

  Int32 Divide(const Int32 other) const noexcept {
    return Int32(_value / other.Value());
  }

  Int32 Modulo(const Int32 other) const noexcept {
    return Int32(_value % other.Value());
  }

  Int32 Negate() const noexcept {
    return Int32(-_value);
  }

  bool Equals(const Int32 other) const noexcept {
    return _value == other.Value();
  }

  Ordering Compare(const Int32 other) const noexcept {
    return Ord<int32_t>::Compare(_value, other.Value());
  }

  Int32 Min(const Int32 other) const noexcept {
    return Int32(Ord<int32_t>::Min(_value, other.Value()));
  }

  Int32 Max(const Int32 other) const noexcept {
    return Int32(Ord<int32_t>::Max(_value, other.Value()));
  }

  double Sqrt() const noexcept {
    return std::sqrt(_value);
  }

  Int32 BinaryAnd(const Int32 other) const noexcept {
    return Int32(_value & other.Value());
  }

  Int32 BinaryOr(const Int32 other) const noexcept {
    return Int32(_value | other.Value());
  }

  Int32 BinaryXor(const Int32 other) const noexcept {
    return Int32(_value ^ other.Value());
  }

  HashValue Hash() const noexcept {
    return HashValue((unsigned int) _value);
  }

  Int32 Copy() const noexcept {
    return Int32(_value);
  }

  String Show() const noexcept {
    return Shows<int32_t>::Show(_value);
  }

  String ToHex() const noexcept {
    return Hexable<int32_t>::ToHex(_value);
  }

  static Int32 MinValue() noexcept {
    return Int32(std::numeric_limits<int32_t>::min());
  }

  static Int32 MaxValue() noexcept {
    return Int32(std::numeric_limits<int32_t>::max());
  }

  static Int32 Zero() noexcept {
    return Int32(0);
  }

  static Int32 One() noexcept {
    return Int32(1);
  }

};

}

