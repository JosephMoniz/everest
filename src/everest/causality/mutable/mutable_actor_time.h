#pragma once

#include <everest/types/string.h>
#include <everest/causality/mutable/mutable_lamport_time.h>

namespace everest {

template <class T>
class MutableActorTime final {

  T _actor;

  MutableLamportTime _time;

public:

  MutableActorTime(const MutableActorTime<T>& other) = delete;

  MutableActorTime(MutableActorTime<T>&& other) noexcept : _actor(std::move(other._actor)),
                                                           _time(other._time) { }

  MutableActorTime(T&& actor, MutableLamportTime&& time) noexcept : _actor(std::move(actor)),
                                                                    _time(std::move(time)) { }

  MutableActorTime<T>& Increment() noexcept {
    _time.Increment();
    return *this;
  }

  const MutableActorTime<T>& Witness(const MutableActorTime<T>& other) noexcept {
    if (_actor == other._actor) {
      _time.Witness(other._time);
    }
    return *this;
  }

  uint64_t Time() const noexcept {
    return _time.Time();
  }

};

}