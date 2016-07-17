#pragma once

#include <everest/crypto/hmac/sha256/hmac_sha256_sink.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class HmacSha256Sink;

template<>
class Sink<HmacSha256Sink> final {
public:

  static constexpr bool exists = true;

  static HmacSha256Sink& PushThrough(const String& input, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  static HmacSha256Sink& PushThrough(String&& input, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(std::move(input));
  }

  template <class T>
  HmacSha256Sink& PushThrough(const Memory<T>& input, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  HmacSha256Sink& PushThrough(const MutableMemory<T>& input, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  HmacSha256Sink& PushThrough(const GrowableMemory<T>& input, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  HmacSha256Sink& PushThrough(uint8_t number, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha256Sink& PushThrough(uint16_t number, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha256Sink& PushThrough(uint32_t number, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha256Sink& PushThrough(uint64_t number, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha256Sink& PushThrough(int8_t number, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha256Sink& PushThrough(int16_t number, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha256Sink& PushThrough(int32_t number, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha256Sink& PushThrough(int64_t number, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha256Sink& PushThrough(size_t size, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(size);
  }

  template <class T>
  static HmacSha256Sink& PushThrough(T&& input, HmacSha256Sink& sink) noexcept {
    return sink.PushThrough(std::forward<T>(input));
  }

  static HmacSha256Digest CloseSink(HmacSha256Sink& sink) noexcept {
    return sink.Hash();
  }

};

}