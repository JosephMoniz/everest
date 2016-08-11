#pragma once

#include <everest/types/string.h>
#include <everest/traits/unlawful/ord/ordering.h>

namespace everest {

class HashValue final {

  unsigned int _hash;

public:

  HashValue(unsigned int hash) noexcept : _hash(hash) { }

  unsigned int Value() const noexcept {
    return _hash;
  }

  bool Equals(const HashValue& other) const noexcept {
    return _hash == other._hash;
  }

  Ordering Compare(const HashValue other) const noexcept {
    return (_hash < other.Value())
      ? Ordering::LESS
      : (_hash > other.Value())
        ? Ordering::GREATER
        : Ordering::EQUAL;
  }

  HashValue Min(const HashValue other) const noexcept {
    return (Compare(other) == Ordering::GREATER)
      ? other
      : *this;
  }

  HashValue Max(const HashValue other) const noexcept {
    return (Compare(other) == Ordering::LESS)
      ? other
      : *this;
  }

};

}