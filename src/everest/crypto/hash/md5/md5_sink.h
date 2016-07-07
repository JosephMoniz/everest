#pragma once

#include <string.h>
#include <openssl/md5.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/crypto/hash/md5/md5_digest.h>
#include <everest/traits/unlawful/funnel.h>

namespace everest {

class Md5Sink final {

  friend class Sink<Md5Sink>;

  MD5_CTX _context;

public:

  Md5Sink() noexcept {
    MD5_Init(&_context);
  }

  Md5Sink& PushThrough(const char* input) noexcept {
    MD5_Update(&_context, input, strlen(input));
    return *this;
  }

  Md5Sink& PushThrough(const String& input) noexcept {
    MD5_Update(&_context, (const unsigned char*)Pointer(input), Length(input));
    return *this;
  }

  Md5Sink& PushThrough(String&& input) noexcept {
    PushThrough(const_cast<const String&>(input));
    return *this;
  }

  template <class T>
  Md5Sink& PushThrough(const Memory<T>& input) noexcept {
    MD5_Update(&_context, (const unsigned char*)Pointer(input), sizeof(T) * Length(input));
    return *this;
  }

  template <class T>
  Md5Sink& PushThrough(const MutableMemory<T>& input) noexcept {
    MD5_Update(&_context, (const unsigned char*)Pointer(input), sizeof(T) * Length(input));
    return *this;
  }

  template <class T>
  Md5Sink& PushThrough(const GrowableMemory<T>& input) noexcept {
    MD5_Update(&_context, (const unsigned char*)Pointer(input), Capacity(input));
    return *this;
  }

  Md5Sink& PushThrough(uint8_t number) noexcept {
    MD5_Update(&_context, &number, sizeof(uint8_t));
    return *this;
  }

  Md5Sink& PushThrough(uint16_t number) noexcept {
    PushThrough((uint8_t)(number & 0xFF));
    PushThrough((uint8_t)((number >> 8) & 0xFF));
    return *this;
  }

  Md5Sink& PushThrough(uint32_t number) noexcept {
    PushThrough((uint8_t)(number & 0xFF));
    PushThrough((uint8_t)((number >> 8) & 0xFF));
    PushThrough((uint8_t)((number >> 16) & 0xFF));
    PushThrough((uint8_t)((number >> 24) & 0xFF));
    return *this;
  }

  Md5Sink& PushThrough(uint64_t number) noexcept {
    for (auto i = 0; i < 64; i += 8) {
      PushThrough((int8_t)((number >> i) & 0xFF));
    }
    return *this;
  }

  Md5Sink& PushThrough(int8_t number) noexcept {
    MD5_Update(&_context, &number, sizeof(int8_t));
    return *this;
  }

  Md5Sink& PushThrough(int16_t number) noexcept {
    PushThrough((int8_t)(number & 0xFF));
    PushThrough((int8_t)((number >> 8) & 0xFF));
    return *this;
  }

  Md5Sink& PushThrough(int32_t number) noexcept {
    PushThrough((int8_t)(number & 0xFF));
    PushThrough((int8_t)((number >> 8) & 0xFF));
    PushThrough((int8_t)((number >> 16) & 0xFF));
    PushThrough((int8_t)((number >> 24) & 0xFF));
    return *this;
  }

  Md5Sink& PushThrough(int64_t number) noexcept {
    for (auto i = 0; i < 64; i += 8) {
      PushThrough((int8_t)((number >> i) & 0xFF));
    }
    return *this;
  }

  Md5Sink& PushThrough(size_t size) noexcept {
    size_t bits = sizeof(size) * 8;
    for (size_t i = 0; i < bits; i += 8) {
      PushThrough((int8_t)((size >> i) & 0xFF));
    }
    return *this;
  }

  template <class T>
  Md5Sink& PushThrough(T&& input) noexcept {
    Funnel<T>::PerformFunnel(input, *this);
    return *this;
  }

  Md5Digest Hash() noexcept {
    Md5Digest digest;
    MD5_Final(MutablePointer(digest), &_context);
    return digest;
  }

};

}

#include <everest/crypto/hash/md5/sink/sink.h>