#pragma once

#include <everest/types/uint64.h>

namespace everest {

class MutableLamportTime final {
public:

  uint64_t _time;

public:

  MutableLamportTime(uint64_t time) noexcept : _time(time) { }

  MutableLamportTime& Increment() noexcept {
    _time += 1;
    return *this;
  }

  const MutableLamportTime Witness(const MutableLamportTime& other) noexcept {
    _time = Max(other._time, time) + 1;
    return *this;
  }

  uint64_t Time() const noexcept {
    return _time;
  }

};

}