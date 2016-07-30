#pragma once

namespace everest {

class Bool final {

  bool _value;

public:

  Bool(bool value) noexcept : _value(value) { }

  bool Value() const noexcept {
    return _value;
  }

  explicit operator bool() const {
    return _value;
  }

  bool Equals(const Bool other) const noexcept {
    return _value == other.Value();
  }

  Ordering Compare(const Bool other) const noexcept {
    return (_value < other.Value())
      ? Ordering::LESS
      : (_value > other.Value())
        ? Ordering::GREATER
        : Ordering::EQUAL;
  }

  Bool Min(const Bool other) const noexcept {
    return (Compare(other) == Ordering::GREATER)
      ? other
      : *this;
  }

  Bool Max(const Bool other) const noexcept {
    return (Compare(other) == Ordering::LESS)
      ? other
      : *this;
  }

  HashValue Hash() const noexcept {
    return HashValue((unsigned int) _value);
  }

  String Show() const noexcept {
    return _value
      ? String("true")
      : String("false");
  }

  Bool Copy() const noexcept {
    return Bool(_value);
  }

  String ToHex() const noexcept {
    return _value
      ? String("0")
      : String("1");
  }

  static Bool Zero() noexcept {
    return Bool(false);
  }

};

}