#pragma once

#include <everest/crypto/hmac/md5/hmac_md5_sink.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class HmacMd5Sink;

template<>
class Sink<HmacMd5Sink> final {
public:

  static constexpr bool exists = true;

  static HmacMd5Sink& PushThrough(const String& input, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  static HmacMd5Sink& PushThrough(String&& input, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(std::move(input));
  }

  template <class T>
  HmacMd5Sink& PushThrough(const Memory<T>& input, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  HmacMd5Sink& PushThrough(const MutableMemory<T>& input, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  HmacMd5Sink& PushThrough(const GrowableMemory<T>& input, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  HmacMd5Sink& PushThrough(uint8_t number, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacMd5Sink& PushThrough(uint16_t number, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacMd5Sink& PushThrough(uint32_t number, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacMd5Sink& PushThrough(uint64_t number, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacMd5Sink& PushThrough(int8_t number, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacMd5Sink& PushThrough(int16_t number, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacMd5Sink& PushThrough(int32_t number, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacMd5Sink& PushThrough(int64_t number, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  HmacMd5Sink& PushThrough(size_t size, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(size);
  }

  template <class T>
  static HmacMd5Sink& PushThrough(T&& input, HmacMd5Sink& sink) noexcept {
    return sink.PushThrough(std::forward<T>(input));
  }

  static HmacMd5Digest CloseSink(HmacMd5Sink& sink) noexcept {
    return sink.Hash();
  }

};

}