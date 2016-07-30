#pragma once

#include <stddef.h>
#include <utility>
#include <everest/memory/mutable_memory.h>

namespace everest {

template<class T>
class Memory final {

  friend class MutableMemory<T>;

  MutableMemory<T> _wrapped;

public:

  Memory() noexcept : _wrapped() { }

  Memory(const T* pointer, size_t length) noexcept : _wrapped(pointer, length) { }

  Memory(const Memory<T>& other) = delete;

  Memory(Memory<T>&& other) noexcept : _wrapped(std::move(other._wrapped)) { }

  Memory(MutableMemory<T>&& other) noexcept : _wrapped(std::move(other)) { }

  Memory& operator=(Memory<T>&& other) noexcept {
    _wrapped = std::move(other._wrapped);
    return *this;
  }

  const T* Pointer() const noexcept {
    return _wrapped.Pointer();
  }

  size_t Length() const noexcept {
    return _wrapped.Length();
  }

  bool IsEmpty() const noexcept {
    return _wrapped.IsEmpty();
  }

};

}
