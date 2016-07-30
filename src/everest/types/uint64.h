#pragma once

#include <cstdint>

namespace everest {

class UInt64 final {

  uint64_t _value;

public:

  UInt64(uint64_t value) noexcept : _value(value) { }

  uint64_t Value() const noexcept {
    return _value;
  }

  explicit operator bool() const {
    return _value != 0;
  }
  operator uint64_t() const {
    return _value;
  }


  UInt64 Add(const UInt64 other) const noexcept {
    return UInt64(_value + other.Value());
  }

  UInt64 Subtract(const UInt64 other) const noexcept {
    return UInt64(_value - other.Value());
  }

  UInt64 Multiply(const UInt64 other) const noexcept {
    return UInt64(_value * other.Value());
  }

  UInt64 Divide(const UInt64 other) const noexcept {
    return UInt64(_value / other.Value());
  }

  UInt64 Modulo(const UInt64 other) const noexcept {
    return UInt64(_value % other.Value());
  }

  bool Equals(const UInt64 other) const noexcept {
    return _value == other.Value();
  }

  Ordering Compare(const UInt64 other) const noexcept {
    return Ord<uint64_t>::Compare(_value, other.Value());
  }

  UInt64 Min(const UInt64 other) const noexcept {
    return UInt64(Ord<uint64_t>::Min(_value, other.Value()));
  }

  UInt64 Max(const UInt64 other) const noexcept {
    return UInt64(Ord<uint64_t>::Max(_value, other.Value()));
  }

  double Sqrt(const UInt64 number) const noexcept {
    return std::sqrt(number.Value());
  }

  UInt64 BinaryAnd(const UInt64 other) const noexcept {
    return UInt64(_value & other.Value());
  }

  UInt64 BinaryOr(const UInt64 other) const noexcept {
    return UInt64(_value | other.Value());
  }

  UInt64 BinaryXor(const UInt64 other) const noexcept {
    return UInt64(_value ^ other.Value());
  }

  HashValue Hash() const noexcept {
    return HashValue((unsigned int) _value);
  }

  UInt64 Copy() const noexcept {
    return UInt64(_value);
  }

  String Show() const noexcept {
    return Shows<uint64_t>::Show(_value);
  }

  String ToHex() const noexcept {
    return Hexable<uint64_t>::ToHex(_value);
  }

  static UInt64 MinValue() noexcept {
    return UInt64(std::numeric_limits<uint64_t>::min());
  }

  static UInt64 MaxValue() noexcept {
    return UInt64(std::numeric_limits<uint64_t>::max());
  }

  static UInt64 Zero() noexcept {
    return UInt64(0);
  }

  static UInt64 One() noexcept {
    return UInt64(1);
  }

};

}

