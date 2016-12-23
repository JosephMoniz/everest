#pragma once

#include <mutex>
#include <everest/concurrency/channel_state.h>
#include <everest/concurrency/channel_result.h>
#include <everest/mutable_containers/mutable_vector.h>
#include <everest/mutable_containers/mutable_circular_buffer.h>

namespace everest {

template <class T>
class Channel final {

  std::shared_ptr<ChannelState<T>> _state;

  Channel<T>& PushThrough(T&& item) noexcept {
    auto lock = _state->ScopedLock();
    _state->WaitForSpace(lock);
    _state->CircularBuffer().Enqueue(std::move(item));
    _state->NotifyReader();
    return *this;
  }

  void CloseSink() noexcept {
    auto lock = _state->ScopedLock();
    _state->Close();
    _state->NotifyAllReaders();
    _state->NotifyAllWriters();
  }

  void Close() noexcept {
    CloseSink();
  }

  Channel<T>& EnqueueInPlace(T&& item) {
    return PushThrough(std::move(item));
  }

  ChannelResult<T> DequeueWithMove() {
    auto lock = _state->ScopedLock();
    _state->WaitForItem(lock);
    if(!_state->CircularBuffer().IsEmpty()) {
      T item = std::move(_state->CircularBuffer().Dequeue()[0]);
      _state->NotifyWriter();
      return ChannelResult<T>::More(std::move(item));
    } else {
      ChannelResult<T>::Done();
    }
  }

public:

  Channel() noexcept : _state(nullptr) { }

  Channel(size_t size) noexcept : _state(std::make_shared<ChannelState<T>>(size)) { }

  Channel(std::shared_ptr<ChannelState<T>>& state) noexcept : _state(state) { }

  Channel(const Channel<T>& other) noexcept : _state(other._state) { }

  Channel(Channel<T>&& other) noexcept : _state(std::move(other._state)) { }

  Channel& operator=(Channel<T>&& other) noexcept {
    _state = std::move(other._state);
    return *this;
  }

  bool IsOpen() const noexcept {
    return _state->IsOpen();
  }

  bool IsClosed() const noexcept {
    return _state->IsClosed();
  }

  class Sink final {

    Channel<T> _channel;

  public:

    Sink(std::shared_ptr<ChannelState<T>>& state) noexcept : _channel(state) { }

    Channel<T>& PushThrough(T&& item) noexcept {
      return _channel.PushThrough(std::move(item));
    }

    void CloseSink() noexcept {
      _channel.CloseSink();
    }

    bool IsOpen() const noexcept {
      return _channel.IsOpen();
    }

    bool IsClosed() const noexcept {
      return _channel.IsClosed();
    }

  };

  class Stream final {

    Channel<T> _channel;

  public:

    Stream() noexcept : _channel() { }

    Stream(std::shared_ptr<ChannelState<T>>& state) noexcept : _channel(state) { }

    Stream(const Channel<T>::Stream& other) noexcept : _channel(other._channel) { }

    Stream(Channel<T>&& other) noexcept : _channel(std::move(other)) { }

    Stream(Channel<T>::Stream&& other) noexcept : _channel(std::move(other._channel)) { }

    Stream& operator=(Channel<T>::Stream&& other) noexcept {
      _channel = std::move(other._channel);
      return *this;
    }

    ChannelResult<T> DequeueWithMove() noexcept {
      return _channel.DequeueWithMove();
    }

    void Close() noexcept {
      _channel.Close();
    }

    template <class F>
    void ForEach(F function) noexcept {
      ChannelResult<T> result;
      while ((result = _channel.DequeueWithMove()).IsMore()) {
        function(result.GetMovable());
      }
    }

    bool IsOpen() const noexcept {
      return _channel.IsOpen();
    }

    bool IsClosed() const noexcept {
      return _channel.IsClosed();
    }

  };

  Sink GetSink() noexcept {
    return Sink(this->_state);
  }

  Stream GetStream() noexcept {
    return Stream(this->_state);
  }

};

}