#pragma once

#include <thread>
#include <everest/concurrency/channel.h>

namespace everest {

class FixedWorkerPool final {

  MutableVector<std::thread> _threads;

  FixedWorkerPool(MutableVector<std::thread>&& threads) noexcept : _threads(std::move(threads)) { }

public:

  FixedWorkerPool(const FixedWorkerPool& other) = delete;

  FixedWorkerPool(FixedWorkerPool&& other) noexcept : _threads(std::move(other._threads)) { }

  FixedWorkerPool& operator=(const FixedWorkerPool& other) = delete;

  FixedWorkerPool& operator=(FixedWorkerPool&& other) noexcept {
    _threads = std::move(other._threads);
  }

  void Join() noexcept {
    _threads.MovingForEach([](std::thread&& thread) {
      thread.join();
    });
  }

  template <class T, class Fn>
  static FixedWorkerPool Work(typename Channel<T>::Stream&& stream, size_t workers, Fn runnable) noexcept {
    MutableVector<std::thread> threads;
    threads.Reserve(workers);
    for (size_t i = 0; i < workers; i++) {
      threads.PushInPlace(std::thread([stream, runnable, i]() mutable {
        stream.ForEach(runnable);
      }));
    }
    return FixedWorkerPool(std::move(threads));
  }

  template <class T>
  class FixedWorkerPoolBuilder final {

    typename Channel<T>::Stream _stream;

    size_t _workers;

    std::function<void(T)> _runnable;

  public:

    FixedWorkerPoolBuilder() noexcept : _stream(), _workers(), _runnable() { }

    FixedWorkerPoolBuilder<T>& SetStream(typename Channel<T>::Stream&& stream) noexcept {
      _stream = std::move(stream);
      return *this;
    }

    FixedWorkerPoolBuilder<T>& SetWorkerCount(size_t workers) noexcept {
      _workers = workers;
      return *this;
    }

    FixedWorkerPoolBuilder<T>& SetRunnable(std::function<void(T)>&& runnable) noexcept {
      _runnable = std::move(runnable);
      return *this;
    }

    FixedWorkerPool Build() noexcept {
      return FixedWorkerPool::Work<T>(std::move(_stream), _workers, std::move(_runnable));
    }

  };

  template <class T>
  static FixedWorkerPoolBuilder<T> Builder() noexcept {
    return FixedWorkerPoolBuilder<T>();
  };

};

}