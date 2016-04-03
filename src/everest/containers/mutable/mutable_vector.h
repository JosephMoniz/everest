#pragma once

#include <stddef.h>
#include <everest/containers/option.h>

namespace everest {

template<class T>
class MutableVector {

  T* _pointer;

  size_t _size;

  size_t _capacity;

public:

  MutableVector() noexcept : MutableVector(32) { }

  MutableVector(size_t capacity) noexcept {
    _size     = 0;
    _capacity = capacity;
    _pointer  = new T[capacity];
  }

  ~MutableVector() {
    delete[] _pointer;
  }

  size_t Size() const noexcept {
    return _size;
  }

  size_t Capacity() const noexcept {
    return _capacity;
  }

  const T* Pointer() const noexcept {
    return _pointer;
  };

  T* MutablePointer() const noexcept {
    return _pointer;
  };

  void Reserve(size_t size) noexcept {
    if (size > _capacity) {
      auto tmp  = _pointer;
      _capacity = size;
      _pointer  = new T[_capacity];
      for (auto i = 0; i < _size; i++) {
        _pointer[i] = tmp[i];
      }
      delete[] tmp;
    }
  }

  void Push(const T& item) noexcept {
    if (_size == _capacity) {
      Reserve(_capacity * 2);
    }
    _pointer[_size++] = item;
  }

  void Push(T&& item) noexcept {
    if (_size == _capacity) {
      Reserve(_capacity * 2);
    }
    _pointer[_size++] = std::move(item);
  }

  void Pop() noexcept {
    if (_size > 0) {
      _size--;
    }
  }

  Option<T&> Front() noexcept {
    if (_size > 0) {
      return Some(_pointer[0]);
    } else {
      return None();
    }
  }

  Option<T&> Back() noexcept {
    if (_size > 0) {
      return Some(_pointer[_size - 1]);
    } else {
      return None();
    }
  }

  Option<T&> At(size_t offset) noexcept {
    if (offset < _size) {
      return Some(_pointer[offset]);
    } else {
      return None();
    }
  }

};



}