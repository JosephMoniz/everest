#pragma once

#include <stddef.h>
#include <utility>
#include <everest/memory/mutable_memory.h>
#include <everest/traits/unlawful/Pointable.h>

namespace everest {

template<class T>
class Memory final {

  friend class Pointable<Memory<T>>;
  friend class Container<Memory<T>>;

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

  Memory() noexcept : _pointer(nullptr), _length(0) { }

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
    copyInit(Pointer(other), Length(other));
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

};

template<class T>
using SharedMemory = Shared<Memory<T>>;

template<class T>
SharedMemory<T> MakeSharedMemory(const T* pointer, size_t length) {
  return MakeShared<Memory<T>>(pointer, length);
}

template <class T>
class Pointable<Memory<T>> {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const Memory<T>& memory) noexcept {
    return (const T*) memory._pointer;
  }

};

template <class T>
class Container<Memory<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const Memory<T>& memory) noexcept {
    return memory._length;
  }

  static constexpr bool IsEmpty(const Memory<T>& memory) noexcept {
    return memory._length == 0;
  }

};

}
