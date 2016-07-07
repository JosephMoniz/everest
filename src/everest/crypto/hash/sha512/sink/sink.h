#pragma once

#include <everest/crypto/hash/sha512/sha512_sink.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class Sha512Sink;

template<>
class Sink<Sha512Sink> final {
public:

  static constexpr bool exists = true;

  static Sha512Sink& PushThrough(const String& input, Sha512Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  static Sha512Sink& PushThrough(String&& input, Sha512Sink& sink) noexcept {
    return sink.PushThrough(std::move(input));
  }

  template <class T>
  Sha512Sink& PushThrough(const Memory<T>& input, Sha512Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  Sha512Sink& PushThrough(const MutableMemory<T>& input, Sha512Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  Sha512Sink& PushThrough(const GrowableMemory<T>& input, Sha512Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  Sha512Sink& PushThrough(uint8_t number, Sha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha512Sink& PushThrough(uint16_t number, Sha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha512Sink& PushThrough(uint32_t number, Sha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha512Sink& PushThrough(uint64_t number, Sha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha512Sink& PushThrough(int8_t number, Sha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha512Sink& PushThrough(int16_t number, Sha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha512Sink& PushThrough(int32_t number, Sha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha512Sink& PushThrough(int64_t number, Sha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha512Sink& PushThrough(size_t size, Sha512Sink& sink) noexcept {
    return sink.PushThrough(size);
  }

  template <class T>
  static Sha512Sink& PushThrough(T&& input, Sha512Sink& sink) noexcept {
    return sink.PushThrough(std::forward<T>(input));
  }

  static Sha512Digest CloseSink(Sha512Sink& sink) noexcept {
    return sink.Hash();
  }

};

}