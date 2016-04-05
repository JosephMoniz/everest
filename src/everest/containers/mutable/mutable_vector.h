#pragma once

#include <stddef.h>
#include <everest/containers/option.h>
#include <everest/memory/mutable_memory.h>

namespace everest {

template<class T>
class Vector;

template<class T>
class MutableVector {

  friend class Vector<T>;

  MutableMemory<T> _memory;

  size_t _length;

public:

  MutableVector() noexcept : MutableVector(32) { }

  MutableVector(size_t capacity) noexcept {
    _length = 0;
    _memory = MutableMemory<T>(capacity);
  }

  size_t Length() const noexcept {
    return _length;
  }

  size_t Capacity() const noexcept {
    return _memory.Length();
  }

  const T* Pointer() const noexcept {
    return _memory.Pointer();
  };

  T* MutablePointer() const noexcept {
    return _memory.MutablePointer();
  };

  void Reserve(size_t size) noexcept {
    if (size > _memory.Length()) {
      auto memory = MutableMemory<T>(size);
      auto dest   = memory.MutablePointer();
      auto src    = _memory.Pointer();
      for (auto i = 0; i < _length; i++) {
        dest[i] = src[i];
      }
      _memory = std::move(memory);
    }
  }

  void Push(const T& item) noexcept {
    if (_length == _memory.Length()) {
      Reserve((size_t) (_memory.Length() * 1.5));
    }
    _memory.MutablePointer()[_length++] = item;
  }

  void Push(T&& item) noexcept {
    if (_length == _memory.Length()) {
      Reserve((size_t) (_memory.Length() * 1.5));
    }
    _memory.MutablePointer()[_length++] = std::move(item);
  }

  void Pop() noexcept {
    if (_length > 0) {
      _length--;
    }
  }

  Option<T&> Front() noexcept {
    if (_length > 0) {
      return Some(_memory.Pointer()[0]);
    } else {
      return None<T&>();
    }
  }

  Option<T&> Back() noexcept {
    if (_length > 0) {
      return Some(_memory.Pointer()[_length - 1]);
    } else {
      return None<T&>();
    }
  }

  Option<T&> At(size_t offset) noexcept {
    if (offset < _length) {
      return Some(_memory.Pointer()[offset]);
    } else {
      return None<T&>();
    }
  }

};



}
