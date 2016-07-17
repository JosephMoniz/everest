#pragma once

#include <cstddef>
#include <everest/containers/mutable/mutable_bit_set.h>

namespace everest {

template<class T, size_t Size, size_t Hashes>
class MutableBloomFilter final {

  MutableBitSet _bits;

public:

  MutableBloomFilter() noexcept : _bits(Size) {

  }

  MutableBloomFilter& Add(const T& item) noexcept {
    auto hash = Hash(item);
    for (size_t i = 0;  i < Hashes; i++) {
      _bits.SetInPlace(MultiHash(i, hash) % Length(_bits), true);
    }
    return *this;
  }

  bool PossiblyContains(const T& item) const noexcept {
    auto hash = Hash(item);
    for (size_t i = 0; i < Hashes; i++) {
      if (!_bits.At(MultiHash(i, hash) % (Length(_bits)))) {
        return false;
      }
    }
    return true;
  }

};

}