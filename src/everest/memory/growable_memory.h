#pragma once

#include <string.h>
#include <everest/memory/mutable_memory.h>

namespace everest {

template <class T>
class GrowableMemory final {

  friend class Container<GrowableMemory<T>>;
  friend class Pointable<GrowableMemory<T>>;
  friend class MutablePointable<GrowableMemory<T>>;

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
    if (_memory == nullptr) {
      _memory = MutableMemory<T>((size == 0) ? 32 : size);
    } else {
      if (size > Length(_memory)) {
        auto old        = std::move(_memory);
        _memory         = MutableMemory<T>(size);
        auto oldPointer = Pointer(old);
        auto newPointer = MutablePointer(_memory);
        memcpy(newPointer, oldPointer, sizeof(T) * Length(old));
      }
    }
  }

  void ReserveAtLeast(size_t size) noexcept {
    auto allocatedSize = Length(_memory) > 0 ? Length(_memory) : 32;
    while (allocatedSize < size) {
      allocatedSize *= 1.5;
    }
    Reserve(allocatedSize);
  }

};

template<class T>
class MutablePointable<GrowableMemory<T>> final {
public:

  static constexpr bool exists = true;

  static T* Pointer(GrowableMemory<T>& memory) noexcept {
    return MutablePointable<MutableMemory<T>>::Pointer(memory._memory);
  }

};

template <class T>
class Pointable<GrowableMemory<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const GrowableMemory<T>& memory) noexcept {
    return Pointable<MutableMemory<T>>::Pointer(memory._memory);
  }

};

template <class T>
class Container<GrowableMemory<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const GrowableMemory<T>& memory) noexcept {
    return Container<MutableMemory<T>>::Length(memory._memory);
  }

  static constexpr bool IsEmpty(const GrowableMemory<T>& memory) noexcept {
    return Container<MutableMemory<T>>::IsEmpty(memory._memory);
  }

};

template<class T>
class Eq<GrowableMemory<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const GrowableMemory<T>& lhs, const GrowableMemory<T>* rhs) noexcept {
    return Equals(&lhs, rhs);
  }

  static bool Equals(const GrowableMemory<T>* lhs, const GrowableMemory<T>& rhs) noexcept {
    return Equals(lhs, &rhs);
  }

  static bool Equals(const GrowableMemory<T>& lhs, const GrowableMemory<T>& rhs) noexcept {
    return Equals(&lhs, &rhs);
  }

  static bool Equals(const GrowableMemory<T>* lhs, const GrowableMemory<T>* rhs) noexcept {
    if (lhs == nullptr) {
      return rhs == nullptr || Pointer(*rhs) == nullptr;
    } else {
      if (rhs == nullptr) {
        return Pointer(*lhs) == nullptr;
      } else {
        auto leftLength = Length(*lhs);
        if (leftLength == Length(*rhs)) {
          return memcmp(Pointer(*lhs), Pointer(*rhs), leftLength) == 0;
        } else {
          return false;
        }
      }
    }
  }

};

}
