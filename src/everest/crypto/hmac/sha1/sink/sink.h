#pragma once

#include <everest/crypto/hmac/sha1/hmac_sha1_sink.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class HmacSha1Sink;

template<>
class Sink<HmacSha1Sink> final {
public:

  static constexpr bool exists = true;

  static HmacSha1Sink& PushThrough(const String& input, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  static HmacSha1Sink& PushThrough(String&& input, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(std::move(input));
  }

  template <class T>
  HmacSha1Sink& PushThrough(const Memory<T>& input, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  HmacSha1Sink& PushThrough(const MutableMemory<T>& input, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  HmacSha1Sink& PushThrough(const GrowableMemory<T>& input, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  HmacSha1Sink& PushThrough(uint8_t number, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha1Sink& PushThrough(uint16_t number, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha1Sink& PushThrough(uint32_t number, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha1Sink& PushThrough(uint64_t number, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha1Sink& PushThrough(int8_t number, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha1Sink& PushThrough(int16_t number, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha1Sink& PushThrough(int32_t number, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha1Sink& PushThrough(int64_t number, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha1Sink& PushThrough(size_t size, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(size);
  }

  template <class T>
  static HmacSha1Sink& PushThrough(T&& input, HmacSha1Sink& sink) noexcept {
    return sink.PushThrough(std::forward<T>(input));
  }

  static HmacSha1Digest CloseSink(HmacSha1Sink& sink) noexcept {
    return sink.Hash();
  }

};

}