#pragma once

#include <stddef.h>
#include <string.h>
#include <everest/memory/memory.h>

namespace everest {

template<class T>
class Memory;

template<class T>
class MutableMemory final {

  friend class Memory<T>;

  T* _pointer;

  size_t _length;

  void copyInit(const T* pointer, size_t length) noexcept {
    _pointer = new T[length];
    for (size_t i = 0; i < length; i++) {
      _pointer[i] = pointer[i];
    }
    _length = length;
  }

public:

  MutableMemory() noexcept : _pointer(nullptr), _length(0) { }

  MutableMemory(size_t length) noexcept {
    _pointer = new T[length];
    _length  = length;
  }

  MutableMemory(const T* pointer, size_t length) noexcept {
    copyInit(pointer, length);
  }

  MutableMemory(const MutableMemory<T>& other) = delete;

  MutableMemory(MutableMemory<T>&& other) noexcept : _pointer(std::move(other._pointer)),
                                                     _length(std::move(other._length))
  {
    other._pointer = nullptr;
    other._length  = 0;
  }

  MutableMemory(Memory<T>&& other) noexcept : MutableMemory(std::move(other._wrapped)) { }

  MutableMemory<T>& operator=(const MutableMemory<T>& other) = delete;

  MutableMemory<T>& operator=(MutableMemory<T>&& other) noexcept {
    if (_pointer != nullptr) {
      delete _pointer;
    }
    _pointer       = other._pointer;
    _length        = other._length;
    other._pointer = nullptr;
    other._length  = 0;
    return *this;
  }

  ~MutableMemory() {
    if (_pointer != nullptr) {
      delete[] _pointer;
    }
  }

  const T* Pointer() const noexcept {
    return (const T*) _pointer;
  }

  T* MutablePointer() noexcept {
    return _pointer;
  }

  size_t Length() const noexcept {
    return _length;
  }

  bool IsEmpty() const noexcept {
    return _length == 0;
  }


  bool Equals(const MutableMemory<T>& other) const noexcept {
    if (other.Pointer() == nullptr) {
      return _pointer == nullptr;
    } else {
      if (_length == other.Length()) {
        return memcmp(_pointer, other.Pointer(), _length) == 0;
      } else {
        return false;
      }
    }
  }

};

}
