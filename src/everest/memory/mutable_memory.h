#pragma once

#include <stddef.h>
#include <everest/memory/shared.h>
#include <everest/traits/unlawful/pointable.h>
#include <everest/traits/unlawful/container.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>
#include "memory.h"

namespace everest {

template<class T>
class Memory;

template<class T>
class MutableMemory final {

  friend class Memory<T>;
  friend class Pointable<MutableMemory<T>>;
  friend class Container<MutableMemory<T>>;
  friend class MutablePointable<MutableMemory<T>>;

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

};

template<class T>
using SharedMutableMemory = Shared<MutableMemory<T>>;

template<class T>
SharedMutableMemory<T> MakeSharedMutableMemory(const T* pointer, size_t length) {
  return MakeShared<MutableMemory<T>>(pointer, length);
}

template<class T>
class Pointable<MutableMemory<T>> {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const MutableMemory<T>& memory) noexcept {
    return (const T*) memory._pointer;
  }

};

template<class T>
class MutablePointable<MutableMemory<T>> {
public:

  static constexpr bool exists = true;

  static T* Pointer(MutableMemory<T>& memory) noexcept {
    return memory._pointer;
  }

};

template <class T>
class Container<MutableMemory<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const MutableMemory<T>& memory) noexcept {
    return memory._length;
  }

  static constexpr bool IsEmpty(const MutableMemory<T>& memory) noexcept {
    return memory._length == 0;
  }

};

template<class T>
class Eq<MutableMemory<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableMemory<T>& lhs, const MutableMemory<T>* rhs) noexcept {
    return Equals(&lhs, rhs);
  }

  static bool Equals(const MutableMemory<T>* lhs, const MutableMemory<T>& rhs) noexcept {
    return Equals(lhs, &rhs);
  }

  static bool Equals(const MutableMemory<T>& lhs, const MutableMemory<T>& rhs) noexcept {
    return Equals(&lhs, &rhs);
  }

  static bool Equals(const MutableMemory<T>* lhs, const MutableMemory<T>* rhs) noexcept {
    if (lhs == nullptr) {
      return rhs == nullptr || Pointer(*rhs) == nullptr;
    } else {
      if (rhs == nullptr) {
        return Pointer(*lhs) == nullptr;
      } else {
        auto leftLength = Length(*lhs);
        if (leftLength == Length(*rhs)) {
          auto lhsPointer = Pointer(*lhs);
          auto rhsPointer = Pointer(*rhs);
          for (size_t i = 0; i < leftLength; i++) {
            if (lhsPointer[i] != rhsPointer[i]) {
              return false;
            }
          }
          return true;
        } else {
          return false;
        }
      }
    }
  }

};

}
