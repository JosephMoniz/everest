#pragma once

#include <stddef.h>
#include <everest/memory/mutable_memory.h>
#include <everest/traits/unlawful/Pointable.h>

namespace everest {

class MutableBitSet {

  MutableMemory<uint8_t> _bits;

  size_t _size;
  
public:

  MutableBitSet() noexcept : MutableBitSet(32) { }

  MutableBitSet(size_t size) noexcept : _size(size) {
    _memory = MutableMemory<uint8_t>((size / 8) + (size % 8 > 0 ? 1 : 0));
    auto p  = Pointer(_memory);
    for (auto i = 0; i < size; i++) {
      p[i] = 0;
    }
  }

  MutableBitSet(const MutableBitSet& other) = delete;

  MutableBitSet(MutableBitSet&& other) noexcept : _bits(std::move(other.bits)),
                                                  _size(other.size) { }

  bool at(size_t offset) const noexcept {
    auto byte = offset / 8;
    auto bit  = offset % 8;
    return Pointer(_bits)[byte] & bit;
  }

  void set(size_t offset, bool bit) noexcept {
    auto byte    = offset / 8;
    auto bit     = offset % 8;
    auto pointer = Pointer(_bits);
    auto current = pointer[byte];
    auto mask    = 1 << bit;
    if (bit) {
      pointer[0] = current | mask;
    } else {
      pointer[0] = current & (~mask);
    }
  }
  
};

}
