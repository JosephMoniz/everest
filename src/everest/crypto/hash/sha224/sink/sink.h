#pragma once

#include <everest/crypto/hash/sha224/sha224_sink.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class Sha224Sink;

template<>
class Sink<Sha224Sink> final {
public:

  static constexpr bool exists = true;

  static Sha224Sink& PushThrough(const String& input, Sha224Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  static Sha224Sink& PushThrough(String&& input, Sha224Sink& sink) noexcept {
    return sink.PushThrough(std::move(input));
  }

  template <class T>
  Sha224Sink& PushThrough(const Memory<T>& input, Sha224Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  Sha224Sink& PushThrough(const MutableMemory<T>& input, Sha224Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  Sha224Sink& PushThrough(const GrowableMemory<T>& input, Sha224Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  Sha224Sink& PushThrough(uint8_t number, Sha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha224Sink& PushThrough(uint16_t number, Sha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha224Sink& PushThrough(uint32_t number, Sha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha224Sink& PushThrough(uint64_t number, Sha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha224Sink& PushThrough(int8_t number, Sha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha224Sink& PushThrough(int16_t number, Sha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha224Sink& PushThrough(int32_t number, Sha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha224Sink& PushThrough(int64_t number, Sha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha224Sink& PushThrough(size_t size, Sha224Sink& sink) noexcept {
    return sink.PushThrough(size);
  }

  template <class T>
  static Sha224Sink& PushThrough(T&& input, Sha224Sink& sink) noexcept {
    return sink.PushThrough(std::forward<T>(input));
  }

  static Sha224Digest CloseSink(Sha224Sink& sink) noexcept {
    return sink.Hash();
  }

};

}