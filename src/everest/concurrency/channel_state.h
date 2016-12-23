#pragma once

#include <mutex>
#include <condition_variable>
#include <everest/mutable_containers/mutable_circular_buffer.h>

namespace everest {

template <class T>
class ChannelState {

  std::mutex _mutex;

  std::condition_variable _fullConditionVariable;

  std::condition_variable _emptyConditionVariable;

  bool _closed;

  MutableCircularBuffer<T> _circularBuffer;

public:

  ChannelState(size_t size) noexcept : _closed(false), _circularBuffer(size) { }

  ~ChannelState() noexcept {
    auto lock = ScopedLock();
    Close();
  }

  std::unique_lock<std::mutex> ScopedLock() noexcept {
    return std::unique_lock<std::mutex>(_mutex);
  }

  MutableCircularBuffer<T>& CircularBuffer() noexcept {
    return _circularBuffer;
  }

  void WaitForSpace(std::unique_lock<std::mutex>& lock) noexcept {
    if (_circularBuffer.IsFull()) {
      _fullConditionVariable.wait(lock, [&]() { return _closed || !_circularBuffer.IsFull(); });
    }
  }

  void WaitForItem(std::unique_lock<std::mutex>& lock) noexcept {
    _emptyConditionVariable.wait(lock, [&](){ return _closed || !_circularBuffer.IsEmpty(); });
  }

  void NotifyReader() noexcept {
    _emptyConditionVariable.notify_one();
  }

  void NotifyAllReaders() noexcept {
    _emptyConditionVariable.notify_all();
  };

  void NotifyWriter() noexcept {
    _fullConditionVariable.notify_one();
  }

  void NotifyAllWriters() noexcept {
    _fullConditionVariable.notify_all();
  };

  void Close() noexcept {
    _closed = true;
  }

  bool IsOpen() const noexcept {
    return !_closed;
  }

  bool IsClosed() const noexcept {
    return _closed;
  }

};

}