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

template <class T>
class Pointable<Memory<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const Memory<T>& memory) noexcept {
    return memory.Pointer();
  }

};

template <class T>
class Container<Memory<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const Memory<T>& memory) noexcept {
    return memory.Length();
  }

  static constexpr bool IsEmpty(const Memory<T>& memory) noexcept {
    return memory.IsEmpty();
  }

};

}
