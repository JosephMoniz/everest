#pragma once

#include <stddef.h>
#include <utility>
#include <everest/memory/mutable_memory.h>
#include <everest/traits/unlawful/Pointable.h>

namespace everest {

template<class T>
class Memory final {

  friend class MutableMemory<T>;
  friend class Pointable<Memory<T>>;
  friend class Container<Memory<T>>;

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

};

template<class T>
using SharedMemory = Shared<Memory<T>>;

template<class T>
SharedMemory<T> MakeSharedMemory(const T* pointer, size_t length) {
  return MakeShared<Memory<T>>(pointer, length);
}

template <class T>
class Pointable<Memory<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const Memory<T>& memory) noexcept {
    return Pointable<MutableMemory<T>>::Pointer(memory._wrapped);
  }

};

template <class T>
class Container<Memory<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const Memory<T>& memory) noexcept {
    return Container<MutableMemory<T>>::Length(memory._wrapped);
  }

  static constexpr bool IsEmpty(const Memory<T>& memory) noexcept {
    return Container<MutableMemory<T>>::IsEmpty(memory._wrapped);
  }

};

}
