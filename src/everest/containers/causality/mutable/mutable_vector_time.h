#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/containers/causality/mutable/mutable_lamport_time.h>


namespace everest {

template <class T>
class MutableVectorTime final {

  T _actor;

  MutableMap<T, uint64_t> _clock;

public:

  MutableVectorTime(T&& actor) noexcept : _actor(std::move(actor)),
                                          _clock() { }

  MutableVectorTime<T>& Increment() noexcept {
    auto actorTime = GetInPlace(_actor, _clock);
    if (actorTime == nullptr) {
      PutInPlace(_actor, MutableLamportTime(1), _clock);
    } else {
      *actorTime += 1;
    }
    return *this;
  }

  const MutableVectorTime<T>& Witness(const MutableVectorTime<T>& other) noexcept {
    ForEach(other._clock, [&](MutableMapEntry<T, MutableLamportTime>& entry) {
      auto actorTime = GetInPlace(entry.ConstKey(), _clock);
      if (actorTime == nullptr) {
        PutInPlace(entry.ConstKey(), entry.ConstValue());
      } else {
        auto otherTime = entry.ConstValue();
        if (*actorTime != otherTime) {
          *actorTime = Max(*actorTime, otherTime);
        }
      }
    });
    return this->Increment();
  }

};

}