#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/crypto/hmac/sha512/hmac_sha512_digest.h>
#include <everest/traits/unlawful/funnel.h>

namespace everest {

class HmacSha512Sink final {

  friend class Sink<HmacSha512Sink>;

  HMAC_CTX _context;

public:

  HmacSha512Sink(const String& key) noexcept {
    HMAC_CTX_init(&_context);
    HMAC_Init_ex(&_context, Pointer(key), (int)Occupied(key), EVP_sha512(), nullptr);
  }

  HmacSha512Sink& PushThrough(const char* input) noexcept {
    HMAC_Update(&_context, (const unsigned char*)input, strlen(input));
    return *this;
  }

  HmacSha512Sink& PushThrough(const String& input) noexcept {
    HMAC_Update(&_context, (const unsigned char*)Pointer(input), Occupied(input));
    return *this;
  }

  HmacSha512Sink& PushThrough(String&& input) noexcept {
    PushThrough(const_cast<const String&>(input));
    return *this;
  }

  template <class T>
  HmacSha512Sink& PushThrough(const Memory<T>& input) noexcept {
    HMAC_Update(&_context, (const unsigned char*)Pointer(input), sizeof(T) * Length(input));
    return *this;
  }

  template <class T>
  HmacSha512Sink& PushThrough(const MutableMemory<T>& input) noexcept {
    HMAC_Update(&_context, (const unsigned char*)Pointer(input), sizeof(T) * Length(input));
    return *this;
  }

  template <class T>
  HmacSha512Sink& PushThrough(const GrowableMemory<T>& input) noexcept {
    HMAC_Update(&_context, (const unsigned char*)Pointer(input), sizeof(T) * Occupied(input));
    return *this;
  }

  HmacSha512Sink& PushThrough(uint8_t number) noexcept {
    HMAC_Update(&_context, &number, sizeof(uint8_t));
    return *this;
  }

  HmacSha512Sink& PushThrough(uint16_t number) noexcept {
    PushThrough((uint8_t)(number & 0xFF));
    PushThrough((uint8_t)((number >> 8) & 0xFF));
    return *this;
  }

  HmacSha512Sink& PushThrough(uint32_t number) noexcept {
    PushThrough((uint8_t)(number & 0xFF));
    PushThrough((uint8_t)((number >> 8) & 0xFF));
    PushThrough((uint8_t)((number >> 16) & 0xFF));
    PushThrough((uint8_t)((number >> 24) & 0xFF));
    return *this;
  }

  HmacSha512Sink& PushThrough(uint64_t number) noexcept {
    for (auto i = 0; i < 64; i += 8) {
      PushThrough((int8_t)((number >> i) & 0xFF));
    }
    return *this;
  }

  HmacSha512Sink& PushThrough(int8_t number) noexcept {
    HMAC_Update(&_context, (const unsigned char*)&number, sizeof(int8_t));
    return *this;
  }

  HmacSha512Sink& PushThrough(int16_t number) noexcept {
    PushThrough((int8_t)(number & 0xFF));
    PushThrough((int8_t)((number >> 8) & 0xFF));
    return *this;
  }

  HmacSha512Sink& PushThrough(int32_t number) noexcept {
    PushThrough((int8_t)(number & 0xFF));
    PushThrough((int8_t)((number >> 8) & 0xFF));
    PushThrough((int8_t)((number >> 16) & 0xFF));
    PushThrough((int8_t)((number >> 24) & 0xFF));
    return *this;
  }

  HmacSha512Sink& PushThrough(int64_t number) noexcept {
    for (auto i = 0; i < 64; i += 8) {
      PushThrough((int8_t)((number >> i) & 0xFF));
    }
    return *this;
  }

  HmacSha512Sink& PushThrough(size_t size) noexcept {
    size_t bits = sizeof(size) * 8;
    for (size_t i = 0; i < bits; i += 8) {
      PushThrough((int8_t)((size >> i) & 0xFF));
    }
    return *this;
  }

  template <class T>
  HmacSha512Sink& PushThrough(T&& input) noexcept {
    Funnel<T>::PerformFunnel(input, *this);
    return *this;
  }

  HmacSha512Digest Hash() noexcept {
    unsigned int len = HmacSha512Digest::size;
    HmacSha512Digest digest;
    HMAC_Final(&_context, MutablePointer(digest), &len);
    HMAC_CTX_cleanup(&_context);
    return digest;
  }

};

}

#include <everest/crypto/hmac/sha512/sink/sink.h>
