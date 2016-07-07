#pragma once

#include <everest/crypto/hash/sha384/sha384_sink.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class Sha384Sink;

template<>
class Sink<Sha384Sink> final {
public:

  static constexpr bool exists = true;

  static Sha384Sink& PushThrough(const String& input, Sha384Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  static Sha384Sink& PushThrough(String&& input, Sha384Sink& sink) noexcept {
    return sink.PushThrough(std::move(input));
  }

  template <class T>
  Sha384Sink& PushThrough(const Memory<T>& input, Sha384Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  Sha384Sink& PushThrough(const MutableMemory<T>& input, Sha384Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  template <class T>
  Sha384Sink& PushThrough(const GrowableMemory<T>& input, Sha384Sink& sink) noexcept {
    return sink.PushThrough(input);
  }

  Sha384Sink& PushThrough(uint8_t number, Sha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha384Sink& PushThrough(uint16_t number, Sha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha384Sink& PushThrough(uint32_t number, Sha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha384Sink& PushThrough(uint64_t number, Sha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha384Sink& PushThrough(int8_t number, Sha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha384Sink& PushThrough(int16_t number, Sha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha384Sink& PushThrough(int32_t number, Sha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha384Sink& PushThrough(int64_t number, Sha384Sink& sink) noexcept {
    return sink.PushThrough(number);
  }

  Sha384Sink& PushThrough(size_t size, Sha384Sink& sink) noexcept {
    return sink.PushThrough(size);
  }

  template <class T>
  static Sha384Sink& PushThrough(T&& input, Sha384Sink& sink) noexcept {
    return sink.PushThrough(std::forward<T>(input));
  }

  static Sha384Digest CloseSink(Sha384Sink& sink) noexcept {
    return sink.Hash();
  }

};

}