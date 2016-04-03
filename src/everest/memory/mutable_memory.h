#pragma once

#include <stddef.h>
#include <everest/memory/shared.h>

namespace everest {

template<class T>
class Memory;

template<class T>
class MutableMemory final {

  friend class Memory<T>;

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

  MutableMemory() noexcept {
    _pointer = nullptr;
    _length  = 0;
  }

  MutableMemory(size_t length) noexcept {
    _pointer = new T[length];
    _length  = length;
  }

  MutableMemory(const T* pointer, size_t length) noexcept {
    copyInit(pointer, length);
  }

  MutableMemory(const MutableMemory<T>& other) noexcept {
    copyInit(other._pointer, other._length);
  }

  MutableMemory(MutableMemory<T>&& other) noexcept : _pointer(std::move(other._pointer)),
                                                     _length(std::move(other._length))
  {
    other._pointer = nullptr;
    other._length  = 0;
  }

  MutableMemory& operator=(const MutableMemory<T>& other) noexcept {
    if (_pointer != nullptr) {
      delete _pointer;
    }
    copyInit(other._pointer, other._length);
    return *this;
  }

  MutableMemory& operator=(MutableMemory<T>&& other) noexcept {
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
      delete _pointer;
    }
  }

  const T* Pointer() const noexcept {
    return _pointer;
  };

  T* MutablePointer() const noexcept {
    return _pointer;
  };

  size_t Length() const noexcept {
    return _length;
  }

};

template<class T>
using SharedMutableMemory = Shared<MutableMemory<T>>;

template<class T>
SharedMutableMemory<T> MakeSharedMutableMemory(const T* pointer, size_t length) {
  return MakeShared<MutableMemory<T>>(pointer, length);
}

}
