#pragma once

#include <cstddef>
#include <everest/mutable_containers/mutable_bit_set.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template<class T, size_t Size, size_t Hashes>
class MutableBloomFilter final {

  MutableBitSet _bits;

public:

  MutableBloomFilter() noexcept : _bits() { }

  MutableBloomFilter(MutableBitSet&& bits) noexcept : _bits(std::move(bits)) { }

  MutableBloomFilter Copy() const noexcept {
    return MutableBloomFilter(_bits.Copy());
  }

  MutableBloomFilter& Add(const T& item) noexcept {
    auto hash = Hash(item);
    for (size_t i = 0;  i < Hashes; i++) {
      _bits.SetInPlace(MultiHash(i, hash).Value() % _bits.Length(), true);
    }
    return *this;
  }

  bool PossiblyContains(const T& item) const noexcept {
    auto hash = Hash(item);
    for (size_t i = 0; i < Hashes; i++) {
      if (!_bits.At(MultiHash(i, hash).Value() % (_bits.Length()))) {
        return false;
      }
    }
    return true;
  }

};

}