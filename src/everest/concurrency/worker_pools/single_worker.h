#pragma once

#include <thread>
#include <everest/concurrency/channel.h>

namespace everest {

template <class T>
class SingleWorker final {

  std::thread _thread;

  SingleWorker(std::thread&& thread) noexcept : _thread(std::move(thread)) { }

public:

  SingleWorker(const SingleWorker<T>& other) = delete;

  SingleWorker(SingleWorker<T>&& other) noexcept : _thread(std::move(other._thread)) { }

  SingleWorker<T>& operator=(const SingleWorker<T>& other) = delete;

  SingleWorker<T>& operator=(SingleWorker<T>&& other) noexcept {
    _thread = std::move(other._thread);
  }

  template <class T, class Fn>
  static SingleWorker<T> ConsumeWork(Channel<T>::Stream stream, Fn runnable) noexcept {
    return SingleWorker(std::thread([stream, runnable]() mutable {
      stream.ForEach(runnable);
    }));
  }

};

}