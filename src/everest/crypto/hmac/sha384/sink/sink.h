#pragma once

#include <everest/crypto/hmac/sha384/hmac_sha384_sink.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class HmacSha384Sink;

template<>
class Sink<HmacSha384Sink> final {
public:

  static constexpr bool exists = true;

  static HmacSha384Sink& PushThrough(const String& input, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  static HmacSha384Sink& PushThrough(String&& input, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(std::move(input));
  }

  template <class T>
  HmacSha384Sink& PushThrough(const Memory<T>& input, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  HmacSha384Sink& PushThrough(const MutableMemory<T>& input, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  HmacSha384Sink& PushThrough(const GrowableMemory<T>& input, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  HmacSha384Sink& PushThrough(uint8_t number, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha384Sink& PushThrough(uint16_t number, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha384Sink& PushThrough(uint32_t number, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha384Sink& PushThrough(uint64_t number, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha384Sink& PushThrough(int8_t number, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha384Sink& PushThrough(int16_t number, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha384Sink& PushThrough(int32_t number, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha384Sink& PushThrough(int64_t number, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacSha384Sink& PushThrough(size_t size, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(size);
  }

  template <class T>
  static HmacSha384Sink& PushThrough(T&& input, HmacSha384Sink& sink) noexcept {
    return sink.PushThrough(std::forward<T>(input));
  }

  static HmacSha384Digest CloseSink(HmacSha384Sink& sink) noexcept {
    return sink.Hash();
  }

};

}