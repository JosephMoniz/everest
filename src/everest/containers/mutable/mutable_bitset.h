#pragma once

#include <stddef.h>
#include <everest/memory/mutable_memory.h>
#include <everest/traits/unlawful/pointable.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class MutableBitSet final {

  static constexpr int _intSize = sizeof(int) * 8;

  MutableMemory<int> _bits;

  size_t _size;
  
public:

  MutableBitSet() noexcept : MutableBitSet(32) { }

  MutableBitSet(size_t size) noexcept : _size(size) {
    _bits  = MutableMemory<int>((size / _intSize) + (size % _intSize > 0 ? 1 : 0));
    auto p = MutablePointer(_bits);
    for (auto i = 0; i < size; i++) {
      p[i] = 0;
    }
  }

  MutableBitSet(const MutableBitSet& other) = delete;

  MutableBitSet(MutableBitSet&& other) noexcept : _bits(std::move(other._bits)),
                                                  _size(other._size) { }

  bool At(size_t offset) const noexcept {
    auto byte = offset / _intSize;
    auto bit  = offset % _intSize;
    return Pointer(_bits)[byte] && bit;
  }

  MutableBitSet& SetInPlace(size_t offset, bool value) noexcept {
    auto byte    = offset / _intSize;
    auto bit     = offset % _intSize;
    auto pointer = MutablePointer(_bits);
    auto current = pointer[byte];
    auto mask    = 1 << bit;
    if (value) {
      pointer[0] = current | mask;
    } else {
      pointer[0] = current & (~mask);
    }
    return *this;
  }
  
};

}
