#pragma once

#include <everest/crypto/hmac/sha224/hmac_sha224_sink.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class HmacSha224Sink;

template<>
class Sink<HmacSha224Sink> final {
public:

  static constexpr bool exists = true;

  static HmacSha224Sink& PushThrough(const String& input, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  static HmacSha224Sink& PushThrough(String&& input, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(std::move(input));
  }

  template <class T>
  HmacSha224Sink& PushThrough(const Memory<T>& input, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  HmacSha224Sink& PushThrough(const MutableMemory<T>& input, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  HmacSha224Sink& PushThrough(const GrowableMemory<T>& input, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  HmacSha224Sink& PushThrough(uint8_t number, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha224Sink& PushThrough(uint16_t number, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha224Sink& PushThrough(uint32_t number, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha224Sink& PushThrough(uint64_t number, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha224Sink& PushThrough(int8_t number, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha224Sink& PushThrough(int16_t number, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha224Sink& PushThrough(int32_t number, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha224Sink& PushThrough(int64_t number, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha224Sink& PushThrough(size_t size, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(size);
  }

  template <class T>
  static HmacSha224Sink& PushThrough(T&& input, HmacSha224Sink& sink) noexcept {
    return sink.PushThrough(std::forward<T>(input));
  }

  static HmacSha224Digest CloseSink(HmacSha224Sink& sink) noexcept {
    return sink.Hash();
  }

};

}