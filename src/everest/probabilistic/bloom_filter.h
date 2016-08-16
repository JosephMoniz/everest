#pragma once

#include <cstddef>
#include <everest/probabilistic/mutable_bloom_filter.h>


namespace everest {

template<class T, size_t Size, size_t Hashes>
class BloomFilter final {

  MutableBloomFilter<T, Size, Hashes> _bloom;

public:

  BloomFilter(MutableBloomFilter&& bloom) noexcept : _bloom(std::move(bloom)) { }

  BloomFilter Add(const T& item) noexcept {
    return BloomFilter(_bloom.Copy().Add(item));
  }

  bool PossiblyContains(const T& item) const noexcept {
    return _bloom.PossiblyContains(item);
  }

};

}