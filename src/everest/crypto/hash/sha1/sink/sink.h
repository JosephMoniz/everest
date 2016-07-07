#pragma once

#include <everest/crypto/hash/sha1/sha1_sink.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class Sha1Sink;

template<>
class Sink<Sha1Sink> final {
public:

  static constexpr bool exists = true;

  static Sha1Sink& PushThrough(const String& input, Sha1Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  static Sha1Sink& PushThrough(String&& input, Sha1Sink& sink) noexcept {
    return sink.PushThrough(std::move(input));
  }

  template <class T>
  Sha1Sink& PushThrough(const Memory<T>& input, Sha1Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  Sha1Sink& PushThrough(const MutableMemory<T>& input, Sha1Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  Sha1Sink& PushThrough(const GrowableMemory<T>& input, Sha1Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  Sha1Sink& PushThrough(uint8_t number, Sha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha1Sink& PushThrough(uint16_t number, Sha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha1Sink& PushThrough(uint32_t number, Sha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha1Sink& PushThrough(uint64_t number, Sha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha1Sink& PushThrough(int8_t number, Sha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha1Sink& PushThrough(int16_t number, Sha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha1Sink& PushThrough(int32_t number, Sha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha1Sink& PushThrough(int64_t number, Sha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha1Sink& PushThrough(size_t size, Sha1Sink& sink) noexcept {
    return sink.PushThrough(size);
  }

  template <class T>
  static Sha1Sink& PushThrough(T&& input, Sha1Sink& sink) noexcept {
    return sink.PushThrough(std::forward<T>(input));
  }

  static Sha1Digest CloseSink(Sha1Sink& sink) noexcept {
    return sink.Hash();
  }

};

}