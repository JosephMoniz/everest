#pragma once

#include <string.h>
#include <everest/memory/mutable_memory.h>

namespace everest {

template <class T>
class GrowableMemory final {

  MutableMemory<T> _memory;

public:

  GrowableMemory() noexcept : _memory() { }

  GrowableMemory(size_t capacity) noexcept : _memory(capacity) { }

  GrowableMemory(const T* pointer, size_t length) noexcept : _memory(pointer, length) { }

  GrowableMemory(const GrowableMemory<T>& other) = delete;

  GrowableMemory(GrowableMemory<T>&& other) noexcept : _memory(std::move(other._memory)) { }

  GrowableMemory(MutableMemory<T>&& memory) noexcept : _memory(std::move(memory)) { }

  GrowableMemory(Memory<T>&& memory) noexcept : _memory(std::move(memory)) { }

  GrowableMemory& operator=(const GrowableMemory& other) = delete;

  GrowableMemory& operator=(GrowableMemory&& other) noexcept {
    _memory = std::move(other._memory);
    return *this;
  }

  void Reserve(size_t size) noexcept {
    if (_memory.Pointer() == nullptr) {
      _memory = MutableMemory<T>((size == 0) ? 32 : size);
    } else {
      if (size > _memory.Length()) {
        auto old        = std::move(_memory);
        _memory         = MutableMemory<T>(size);
        auto oldPointer = old.Pointer();
        auto newPointer = _memory.MutablePointer();
        memcpy(newPointer, oldPointer, sizeof(T) * old.Length());
      }
    }
  }

  void ReserveAtLeast(size_t size) noexcept {
    auto allocatedSize = _memory.Length() > 0 ? _memory.Length() : 32;
    while (allocatedSize < size) {
      allocatedSize *= 1.5;
    }
    Reserve(allocatedSize);
  }

  const T* Pointer() const noexcept {
    return _memory.Pointer();
  }

  T* MutablePointer() noexcept {
    return _memory.MutablePointer();
  }

  size_t Length() const noexcept {
    return _memory.Length();
  }

  bool IsEmpty() const noexcept {
    return _memory.IsEmpty();
  }

  bool Equals(const GrowableMemory<T>& rhs) const noexcept {
    if (Length() == rhs.Length()) {
      return memcmp(Pointer(), rhs.Pointer(), Length()) == 0;
    } else {
      return false;
    }
  }

};

}
