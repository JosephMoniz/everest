#pragma once

#include <cstdint>

namespace everest {

class Int64 final {

  int64_t _value;

public:

  Int64(int64_t value) noexcept : _value(value) { }

  int64_t Value() const noexcept {
    return _value;
  }

  explicit operator bool() const {
    return _value != 0;
  }

  operator int64_t() const {
    return _value;
  }

  Int64 Add(const Int64 other) const noexcept {
    return Int64(_value + other.Value());
  }

  Int64 Subtract(const Int64 other) const noexcept {
    return Int64(_value - other.Value());
  }

  Int64 Multiply(const Int64 other) const noexcept {
    return Int64(_value * other.Value());
  }

  Int64 Divide(const Int64 other) const noexcept {
    return Int64(_value / other.Value());
  }

  Int64 Modulo(const Int64 other) const noexcept {
    return Int64(_value % other.Value());
  }

  Int64 Negate() const noexcept {
    return Int64(-_value);
  }

  bool Equals(const Int64 other) const noexcept {
    return _value == other.Value();
  }

  Ordering Compare(const Int64 other) const noexcept {
    return Ord<int64_t>::Compare(_value, other.Value());
  }

  Int64 Min(const Int64 other) const noexcept {
    return Int64(Ord<int64_t>::Min(_value, other.Value()));
  }

  Int64 Max(const Int64 other) const noexcept {
    return Int64(Ord<int64_t>::Max(_value, other.Value()));
  }

  double Sqrt() const noexcept {
    return std::sqrt(_value);
  }

  Int64 BinaryAnd(const Int64 other) const noexcept {
    return Int64(_value & other.Value());
  }

  Int64 BinaryOr(const Int64 other) const noexcept {
    return Int64(_value | other.Value());
  }

  Int64 BinaryXor(const Int64 other) const noexcept {
    return Int64(_value ^ other.Value());
  }

  HashValue Hash() const noexcept {
    return HashValue((unsigned int) _value);
  }

  Int64 Copy() const noexcept {
    return Int64(_value);
  }

  String Show() const noexcept {
    return Shows<int64_t>::Show(_value);
  }

  String ToHex() const noexcept {
    return Hexable<int64_t>::ToHex(_value);
  }

  static Int64 MinValue() noexcept {
    return Int64(std::numeric_limits<int64_t>::min());
  }

  static Int64 MaxValue() noexcept {
    return Int64(std::numeric_limits<int64_t>::max());
  }

  static Int64 Zero() noexcept {
    return Int64(0);
  }

  static Int64 One() noexcept {
    return Int64(1);
  }

};

}

