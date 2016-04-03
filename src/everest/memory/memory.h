#pragma once

#include <stddef.h>
#include <utility>
#include <everest/memory/mutable_memory.h>

namespace everest {

template<class T>
class Memory final {

  T*_pointer;

  size_t _length;

  void copyInit(const T* pointer, size_t length) noexcept {
    _pointer = new T[length];
    for (size_t i = 0; i < length; i++) {
      _pointer[i] = pointer[i];
    }
    _length = length;
  }

public:

  Memory(const T* pointer, size_t length) noexcept {
    copyInit(pointer, length);
  }

  Memory(const Memory<T>& other) noexcept {
    copyInit(other._pointer, other._length);
  }

  Memory(Memory<T>&& other) noexcept : _pointer(std::move(other._pointer)),
                                       _length(std::move(other._length))
  {
    other._pointer = nullptr;
    other._length  = 0;
  }

  Memory(const MutableMemory<T>& other) noexcept {
    copyInit(other.Pointer(), other.Length());
  }

  Memory(MutableMemory<T>&& other) noexcept : _pointer(std::move(other._pointer)),
                                              _length(std::move(other._length))
  {
    other._pointer = nullptr;
    other._length  = 0;
  }

  Memory& operator=(Memory<T>&& other) noexcept {
    if (_pointer != nullptr) {
      delete _pointer;
    }
    _pointer       = other._pointer;
    _length        = other._length;
    other._pointer = nullptr;
    other._length  = 0;
    return *this;
  }

  ~Memory() {
    if (_pointer != nullptr) {
      delete _pointer;
    }
  }

  const T* Pointer() const noexcept {
    return _pointer;
  };

  size_t Length() const noexcept {
    return _length;
  }

};

template<class T>
using SharedMemory = Shared<Memory<T>>;

template<class T>
SharedMemory<T> MakeSharedMemory(const T* pointer, size_t length) {
  return MakeShared<Memory<T>>(pointer, length);
}

}