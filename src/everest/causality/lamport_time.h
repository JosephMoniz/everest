#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

class LamportTime final {

  uint64_t _time;

public:

  LamportTime(uint64_t time) noexcept : _time(time) { }

  const LamportTime Increment() const noexcept {
    return LamportTime(_time + 1);
  }

  const LamportTime Witness(const LamportTime& other) const noexcept {
    return LamportTime(Max(other._time, _time) + 1);
  }

  uint64_t Time() const noexcept {
    return _time;
  }

};

}