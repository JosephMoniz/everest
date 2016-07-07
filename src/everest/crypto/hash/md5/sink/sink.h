#pragma once

#include <everest/crypto/hash/md5/md5_sink.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class Md5Sink;

template<>
class Sink<Md5Sink> final {
public:

  static constexpr bool exists = true;

  static Md5Sink& PushThrough(const String& input, Md5Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  static Md5Sink& PushThrough(String&& input, Md5Sink& sink) noexcept {
    return sink.PushThrough(std::move(input));
  }

  template <class T>
  Md5Sink& PushThrough(const Memory<T>& input, Md5Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  Md5Sink& PushThrough(const MutableMemory<T>& input, Md5Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  Md5Sink& PushThrough(const GrowableMemory<T>& input, Md5Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  Md5Sink& PushThrough(uint8_t number, Md5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Md5Sink& PushThrough(uint16_t number, Md5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Md5Sink& PushThrough(uint32_t number, Md5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Md5Sink& PushThrough(uint64_t number, Md5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Md5Sink& PushThrough(int8_t number, Md5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Md5Sink& PushThrough(int16_t number, Md5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Md5Sink& PushThrough(int32_t number, Md5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Md5Sink& PushThrough(int64_t number, Md5Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Md5Sink& PushThrough(size_t size, Md5Sink& sink) noexcept {
    return sink.PushThrough(size);
  }

  template <class T>
  static Md5Sink& PushThrough(T&& input, Md5Sink& sink) noexcept {
    return sink.PushThrough(std::forward<T>(input));
  }

  static Md5Digest CloseSink(Md5Sink& sink) noexcept {
    return sink.Hash();
  }

};

}