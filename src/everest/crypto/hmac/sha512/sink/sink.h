#pragma once

#include <everest/crypto/hmac/sha512/hmac_sha512_sink.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class HmacSha512Sink;

template<>
class Sink<HmacSha512Sink> final {
public:

  static constexpr bool exists = true;

  static HmacSha512Sink& PushThrough(const String& input, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  static HmacSha512Sink& PushThrough(String&& input, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(std::move(input));
  }

  template <class T>
  HmacSha512Sink& PushThrough(const Memory<T>& input, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  HmacSha512Sink& PushThrough(const MutableMemory<T>& input, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  HmacSha512Sink& PushThrough(const GrowableMemory<T>& input, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  HmacSha512Sink& PushThrough(uint8_t number, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha512Sink& PushThrough(uint16_t number, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha512Sink& PushThrough(uint32_t number, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha512Sink& PushThrough(uint64_t number, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha512Sink& PushThrough(int8_t number, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha512Sink& PushThrough(int16_t number, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha512Sink& PushThrough(int32_t number, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha512Sink& PushThrough(int64_t number, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha512Sink& PushThrough(size_t size, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(size);
  }

  template <class T>
  static HmacSha512Sink& PushThrough(T&& input, HmacSha512Sink& sink) noexcept {
    return sink.PushThrough(std::forward<T>(input));
  }

  static HmacSha512Digest CloseSink(HmacSha512Sink& sink) noexcept {
    return sink.Hash();
  }

};

}