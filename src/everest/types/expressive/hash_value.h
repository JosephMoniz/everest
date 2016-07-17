#pragma once

#include <everest/types/string.h>

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

};

}