#pragma once

#include <uv.h>

namespace everest {

class EventLoop final {
public:

  uv_loop_t _loop;

  EventLoop() noexcept {
    uv_loop_init(&_loop);
  };

  ~EventLoop() noexcept {
    uv_loop_close(&_loop);
  }

  uint64_t Now() const noexcept {
    return uv_now(&_loop);
  }

  void Run() noexcept {
    uv_run(&_loop, UV_RUN_DEFAULT);
  }

  void RunOnce() noexcept {
    uv_run(&_loop, UV_RUN_ONCE);
  }

  uv_loop_t* UVLoop() noexcept {
    return &_loop;
  }

};

}