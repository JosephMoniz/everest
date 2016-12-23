#pragma once

#include <everest/memory/mutable_memory.h>
#include <everest/containers/option.h>

namespace everest {

template <class T>
class MutableCircularBuffer final {

  MutableMemory<T> _memory;

  size_t _maxSize;

  size_t _size;

  size_t _start;

  size_t _end;

public:

  MutableCircularBuffer(size_t size) noexcept : _memory(size),
                                                _maxSize(size),
                                                _size(0),
                                                _start(0),
                                                _end(0) { }

  size_t Length() const noexcept {
    return _size;
  }

  bool IsEmpty() const noexcept {
    return _size == 0;

  }

  bool IsFull() const noexcept {
    return _size == _maxSize;
  }

  bool Enqueue(T&& item) {
    if (_size != _maxSize) {
      auto pointer  = _memory.MutablePointer();
      pointer[_end] = std::move(item); // TODO: i dont't think this move is working
      _end = (_end + 1) % _maxSize;
      _size++;
      return true;
    } else {
      return false;
    }
  }

  T* Dequeue() noexcept {
    if (_size > 0) {
      auto pointer = _memory.MutablePointer();
      auto offset  = _start;
      _start = (_start + 1) % _maxSize;
      _size--;
      return &pointer[offset];
    } else {
      return nullptr;
    }
  }

};

}