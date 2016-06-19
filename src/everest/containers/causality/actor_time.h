#pragma once

#include <everest/types/string.h>
#include <everest/containers/causality/lamport_time.h>

namespace everest {

class ActorTime final {

  String _actor;

  LamportTime _time;

public:

  ActorTime(const ActorTime& other) = delete;

  ActorTime(ActorTime&& other) noexcept : _actor(std::move(other._actor)),
                                          _time(other._time) { }

  ActorTime(String&& actor, LamportTime&& time) noexcept : _actor(std::move(actor)),
                                                           _time(std::move(time)) { }

};

}