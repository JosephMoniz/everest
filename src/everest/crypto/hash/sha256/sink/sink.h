#pragma once

#include <everest/crypto/hash/sha256/sha256_sink.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class Sha256Sink;

template<>
class Sink<Sha256Sink> final {
public:

  static constexpr bool exists = true;

  static Sha256Sink& PushThrough(const String& input, Sha256Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  static Sha256Sink& PushThrough(String&& input, Sha256Sink& sink) noexcept {
    return sink.PushThrough(std::move(input));
  }

  template <class T>
  Sha256Sink& PushThrough(const Memory<T>& input, Sha256Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  Sha256Sink& PushThrough(const MutableMemory<T>& input, Sha256Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  Sha256Sink& PushThrough(const GrowableMemory<T>& input, Sha256Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  Sha256Sink& PushThrough(uint8_t number, Sha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha256Sink& PushThrough(uint16_t number, Sha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha256Sink& PushThrough(uint32_t number, Sha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha256Sink& PushThrough(uint64_t number, Sha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha256Sink& PushThrough(int8_t number, Sha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha256Sink& PushThrough(int16_t number, Sha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha256Sink& PushThrough(int32_t number, Sha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha256Sink& PushThrough(int64_t number, Sha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha256Sink& PushThrough(size_t size, Sha256Sink& sink) noexcept {
    return sink.PushThrough(size);
  }

  template <class T>
  static Sha256Sink& PushThrough(T&& input, Sha256Sink& sink) noexcept {
    return sink.PushThrough(std::forward<T>(input));
  }

  static Sha256Digest CloseSink(Sha256Sink& sink) noexcept {
    return sink.Hash();
  }

};

}