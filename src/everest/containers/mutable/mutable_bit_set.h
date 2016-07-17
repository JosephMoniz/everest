#pragma once

#include <stddef.h>
#include <string.h>
#include <everest/memory/mutable_memory.h>
#include <everest/traits/unlawful/pointable.h>
#include <everest/traits/unlawful/copyable.h>
#include <everest/traits/unlawful/containable.h>
#include <everest/types/string.h>

namespace everest {

class MutableBitSet final {

  friend class Pointable<MutableBitSet>;
  friend class MutablePointable<MutableBitSet>;
  friend class Copyable<MutableBitSet>;
  friend class Containable<MutableBitSet>;
  friend class Container<MutableBitSet>;

  MutableMemory<int> _bits;

  size_t _size;
  
public:

  static constexpr int intSize = sizeof(int) * 8;

  MutableBitSet() noexcept : MutableBitSet(32) { }

  MutableBitSet(size_t size) noexcept : _size(size) {
    auto chunks = sizeToChunks(size);
    _bits       = MutableMemory<int>(chunks);
    memset(MutablePointer(_bits), 0, chunks);
  }

  MutableBitSet(const MutableBitSet& other) = delete;

  MutableBitSet(MutableBitSet&& other) noexcept : _bits(std::move(other._bits)),
                                                  _size(other._size) { }

  static constexpr size_t sizeToChunks(size_t size) noexcept {
    return (size / MutableBitSet::intSize) + (size % MutableBitSet::intSize > 0 ? 1 : 0);
  }

  bool At(size_t offset) const noexcept {
    auto chunks = offset / intSize;
    auto bit    = offset % intSize;
    return Pointer(_bits)[chunks] && bit;
  }

  MutableBitSet& SetInPlace(size_t offset, bool value) noexcept {
    auto chunks  = offset / intSize;
    auto bit     = offset % intSize;
    auto pointer = MutablePointer(_bits);
    auto current = pointer[chunks];
    auto mask    = 1 << bit;
    if (value) {
      pointer[chunks] = current | mask;
    } else {
      pointer[chunks] = current & (~mask);
    }
    return *this;
  }
  
};

template <>
class Pointable<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  static const int* Pointer(const MutableBitSet& bitSet) noexcept {
    return Pointable<MutableMemory<int>>::Pointer(bitSet._bits);
  }

};

template <>
class MutablePointable<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  static int* Pointer(MutableBitSet& bitSet) noexcept {
    return MutablePointable<MutableMemory<int>>::Pointer(bitSet._bits);
  }

};

template <>
class Copyable<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  static MutableBitSet Copy(const MutableBitSet& bitSet) noexcept {
    auto copy = MutableBitSet(bitSet._size);
    memcpy(MutablePointer(copy), Pointer(bitSet), MutableBitSet::sizeToChunks(bitSet._size));
    return copy;
  }

};

template <>
class Containable<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(bool bit, const MutableBitSet& bitSet) noexcept {
    auto pointer = Pointer(bitSet);
    auto chunks  = MutableBitSet::sizeToChunks(bitSet._size);
    if (bit) {
      for (size_t i = 0; i < chunks; i++) {
        if (pointer[i] != 0) {
          return true;
        }
      }
      return false;
    } else {
      for (size_t i = 0; i < chunks; i++) {
        if (pointer[i] != 0xFF) {
          return true;
        }
      }
      return false;
    }
  }

};


template <>
class Container<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const MutableBitSet& bitSet) noexcept {
    return bitSet._size;
  }

  static constexpr bool IsEmpty(const MutableBitSet& bitSet) noexcept {
    return !Containable<MutableBitSet>::Contains(true, bitSet);
  }

};

template <>
class Iteration<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableBitSet& bitSet, const F& function) noexcept {
    auto pointer = Pointer(bitSet);
    auto bits    = Length(bitSet);
    auto eChunks = (bits / MutableBitSet::intSize);
    auto rBits   = bits % MutableBitSet::intSize;
    auto chunks  = eChunks + (rBits > 0 ? 1 : 0);
    auto highBit = 1 << (MutableBitSet::intSize - 1);
    for (size_t i = 0; i < eChunks; i++) {
      for (size_t j = 0; j < MutableBitSet::intSize; j++) {
        function(((pointer[i] << j) & highBit) != 0);
      }
    }
    if (chunks != eChunks) {
      for (size_t j = (MutableBitSet::intSize - rBits); j < MutableBitSet::intSize; j++) {
        function(((pointer[eChunks] << j) & highBit) != 0);
      }
    }
  }

};

template <>
class Shows<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  static String Show(const MutableBitSet& bitSet) noexcept {
    auto out = String("MutableBitSet(");
    ForEach(bitSet, [&](bool bit) {
      out = std::move(out) + String((bit ? "1" : "0"));
    });
    return std::move(out) + String(")");
  }

};

}
