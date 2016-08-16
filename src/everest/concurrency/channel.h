#pragma once

#include <mutex>
#include <everest/mutable_containers/mutable_vector.h>
#include <everest/concurrency/channel_result.h>
#include <everest/mutable_containers/circular_buffer.h>

namespace everest {

template <class T>
class Channel final {

  std::mutex _mutex;

  std::condition_variable _fullConditionVariable;

  std::condition_variable _emptyConditionVariable;

  bool closed;

  CircularBuffer<T> _circularBuffer;

  Channel<T>& PushThrough(T&& item) noexcept {
    std::unique_lock<std::mutex> lock(_mutex);
    if (_circularBuffer.IsFull()) {
      _fullConditionVariable.wait(lock, []() { return closed || !_circularBuffer.IsFull(); });
    }
    _circularBuffer.Enqueue(std::move(item));
    _emptyConditionVariable.notify_one();
  }

  void CloseSink() noexcept {
    std::unique_lock<std::mutex> lock(_mutex);
    closed = true;
    _emptyConditionVariable.notify_all();
  }

  Channel<T>& EnqueueInPlace(T&& item) {
    return PushThrough(std::move(item));
  }

  ChannelResult<T> DequeueWithMove() {
    std::unique_lock<std::mutex> lock(_mutex);
    _emptyConditionVariable.wait(lock, [&](){ return closed || !_circularBuffer.IsEmpty(); });
    auto item = std::move(_circularBuffer.Dequeue());
    _fullConditionVariable.notify_one();
    return _circularBuffer.IsEmpty()
      ? ChannelResult<T>::Done()
      : ChannelResult<T>::More(std::move(item));
  }

public:

  Channel(size_t size) noexcept : closed(false), _circularBuffer(size) { }

  class ChannelSink final {

    Channel& _channel;

  public:

    ChannelSink(Channel& channel) noexcept : _channel(channel) { }

    Channel<T>& PushThrough(T&& item) noexcept {
      return _channel.PushThrough(std::move(item));
    }

    void CloseSink(T& sink) noexcept {
      _channel.CloseSink();
    }

  };

  class ChannelStream final {

    Channel& _channel;

  public:

    ChannelStream(Channel& channel) noexcept : _channel(channel) { }

    ChannelResult<T> DequeueWithMove() {
      return _channel.DequeueWithMove();
    }

    template <class F>
    void ForEach(F function) const noexcept {
      ChannelResult<T> result;
      while ((result = _channel.DequeueWithMove()).IsMore()) {
        function(result.Get());
      }
    }

  };

  ChannelSink GetSink() noexcept {
    return ChannelSink(*this);
  }

  ChannelStream GetStream() noexcept {
    return ChannelStream(*this);
  }

};

}